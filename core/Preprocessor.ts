import assert from "assert";
import Character from "./Character";
import ErrorFormatter from "./ErrorFormatter";

export enum PreprocessorNodeType {
    IfDefined,
    IfNotDefined,
    If,
    EndIf,
    Else,
    Include,
    Define,
    Undefine,
    Error,
    Warning,
    Line,
    Pragma,
    Extension,
    Version
}

export interface IPreprocessorDefineNode {
    type: PreprocessorNodeType.Define;
    arguments: Uint8Array[];
    value: Uint8Array;
    name: Uint8Array;
}

export type PreprocessorNode = IPreprocessorDefineNode;

export default class Preprocessor {
    readonly #contents;
    readonly #errorFormatter;
    readonly #tokens = new Array<PreprocessorNode>();
    #offset = 0;
    public constructor({
        contents,
        file
    }: {
        contents: Uint8Array;
        file: string;
    }) {
        this.#errorFormatter = new ErrorFormatter({
            contents,
            file,
            offset: () => this.#offset
        });
        this.#contents = contents;
    }
    public preprocess() {
        while (!this.#eof()) {
            if (
                Character.isWhiteSpace(this.#current()) ||
                Character.isLineBreak(this.#current())
            ) {
                this.#offset++;
            } else if (this.#read("#")) {
                /**
                 * skip whitespace in case of #  include cases
                 */
                this.#trim();
                const directiveName = this.#readIdentifier();
                /**
                 * skip whitespace after directive name for cases like
                 * - #define              A 1
                 */
                this.#trim();
                switch (Buffer.from(directiveName).toString("utf8")) {
                    case "define": {
                        this.#readDefine();
                        break;
                    }
                }
            } else {
                this.#offset++;
            }
        }
    }
    #readDefine() {
        const name = this.#readIdentifier();
        /**
         * arguments of the define
         */
        const argumentNames = new Array<Uint8Array>();
        /**
         * Only if the define name is immediately followed by an opening parenthesis, then it has arguments.
         *
         * Combinations such as:
         *
         * - #define SAME (ARGUMENT1) ARGUMENT1
         *
         * Should not be interpreted as function macros, but as a simple define.
         */
        if (this.#read("(")) {
            do {
                /**
                 * skip all white spaces before the argument name. this will serve for the scenarios below:
                 * - opening parenthesis is followed by a whitespace
                 *   - #define SAME(   ARGUMENT1) ARGUMENT1
                 *                  ^^^
                 * - comma was read, but the next characters are one or more white spaces
                 *   - #define SUM(   ARGUMENT1,   ARGUMENT2) ARGUMENT1 * ARGUMENT2
                 *                              ^^^
                 */
                this.#trim();
                /**
                 * break here, because if ... is found, it should always be the last argument, so we want to reach the closing parenthesis
                 * immediately after this dot spread
                 */
                if (this.#peek("...")) {
                    break;
                }
                const argumentName = this.#readIdentifier();
                /**
                 * skip whitespace after argument name
                 */
                this.#trim();
                /**
                 * add argument to the argument list
                 */
                argumentNames.push(argumentName);
            } while (this.#read(","));
            /**
             * read variadic arguments
             */
            const variadicArguments = this.#read("...");
            if (variadicArguments !== null) {
                argumentNames.push(variadicArguments);
            }
            /**
             * expect closing parenthesis
             */
            this.#expect(")");
            console.log(
                Buffer.from(name).toString("utf8"),
                argumentNames.map((arg) => Buffer.from(arg).toString("utf8"))
            );
            return;
        }
        const valueStartByteOffset = this.#offset;
        while (!this.#eof() && !this.#peek("\n")) {
            if (this.#peek("\\")) {
                this.#readUntil("\n");
                this.#expect("\n");
            } else {
                this.#offset++;
            }
        }
        this.#tokens.push({
            type: PreprocessorNodeType.Define,
            name,
            arguments: argumentNames,
            value: this.#contents.subarray(valueStartByteOffset, this.#offset)
        });
    }
    #trim() {
        this.#readAsLongAs(Character.isWhiteSpace);
    }
    #expect(value: string) {
        assert.strict.ok(
            this.#read(value),
            this.#errorFormatter.format(`Expected ${value}`)
        );
    }
    #readUntil(value: string) {
        while (!this.#eof() && !this.#peek(value)) {
            this.#offset++;
        }
    }
    #readAsLongAs(validate: (ch: number) => boolean) {
        while (!this.#eof() && validate(this.#current())) {
            this.#offset++;
        }
    }
    #readIdentifier() {
        assert.strict.ok(
            Character.isIdentifierStart(this.#current()),
            this.#errorFormatter.format(`Expected identifier part`)
        );
        const start = this.#offset;
        while (!this.#eof() && Character.isIdentifierPart(this.#current())) {
            this.#offset++;
        }
        return this.#contents.subarray(start, this.#offset);
    }
    #current() {
        const ch = this.#eof() ? undefined : this.#contents[this.#offset];
        assert.strict.ok(
            typeof ch !== "undefined",
            this.#errorFormatter.format(`Unexpected EOF`)
        );
        return ch;
    }
    #read(value: string) {
        const match = this.#peek(value);
        if (match === null) {
            return null;
        }
        this.#offset += match.byteLength;
        return match;
    }
    #peek(value: string) {
        if (this.#eof()) {
            return null;
        }
        const encoded = new TextEncoder().encode(value);
        const remaining = this.#contents.byteLength - this.#offset;
        if (encoded.byteLength > remaining) {
            return null;
        }
        for (let i = 0; i < encoded.byteLength; i++) {
            if (encoded[i] !== this.#contents[this.#offset + i]) {
                return null;
            }
        }
        return this.#contents.subarray(
            this.#offset,
            this.#offset + encoded.byteLength
        );
    }
    #eof() {
        return this.#offset >= this.#contents.byteLength;
    }
}
