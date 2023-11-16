import assert from "assert";
import Character from "./Character";

export enum TokenType {
    LiteralNumber,
    LiteralString,
    Identifier,
    Punctuator,
}

export interface IToken {
    type: TokenType;
    value: Uint8Array;
}

export default class Tokenizer {
    readonly #contents;
    readonly #file;
    readonly #tokens = new Array<IToken>();
    #offset;
    public constructor({
        contents,
        file,
    }: {
        contents: Uint8Array;
        file: string;
    }) {
        this.#contents = contents;
        this.#offset = 0;
        this.#file = file;
    }
    public tokenize() {
        while (!this.#eof()) {
            const ch = this.#current();
            if (
                Character.isTab(ch) ||
                Character.isLineBreak(ch) ||
                Character.isWhiteSpace(ch)
            ) {
                this.#offset++;
            } else if (ch === 35) {
                this.#expect("#");
                while (!this.#eof() && !this.#peek("\n")) {
                    if (this.#peek("\\")) {
                        this.#readUntil("\n");
                        this.#expect("\n");
                    } else {
                        this.#offset++;
                    }
                }
            } else if (this.#peek("//")) {
                this.#expect("//");
                while (!this.#eof() && !this.#peek("\n")) {
                    this.#offset++;
                }
                this.#expect("\n");
            } else if (this.#read("/*")) {
                while (!this.#eof() && !this.#peek("*/")) {
                    this.#offset++;
                }
                this.#expect("*/");
            } else if (Character.isIdentifierStart(ch)) {
                this.#readIdentifier();
            } else if (this.#isLiteralNumberStart()) {
                this.#readLiteralNumber();
            } else {
                assert.strict.ok(
                    this.#readPunctuator(),
                    `${this.#hrPosition()} unexpected character (${ch}) ${new TextDecoder().decode(
                        new Uint8Array([ch])
                    )}:\n${new TextDecoder().decode(
                        this.#contents.subarray(
                            this.#offset,
                            this.#offset + 100
                        )
                    )}`
                );
            }
        }
        return this.#tokens;
    }
    #isLiteralNumberStart() {
        let ch: number;
        /**
         * if current character is a plus sign, negative sign or a dot, set `ch` to the next character,
         * so it can be checked by the end of the method if it's whether an integer part or not (0-9).
         */
        if (this.#peek(".") || this.#peek("+") || this.#peek("-")) {
            ch = this.#charCode(1);
        } else {
            /**
             * in case there's no sign or dot, then do the last check by checking if the current `ch` is an integer part.
             */
            ch = this.#current();
        }
        /**
         * here we check the character after the sign or dot is a sign, or if the current character is a sign
         */
        return Character.isIntegerPart(ch);
    }
    #readAsLongAs(validate: (ch: number) => boolean) {
        while (!this.#eof() && validate(this.#current())) {
            this.#offset++;
        }
    }
    #readLiteralNumber() {
        const start = this.#offset;
        // -1 or +1 or .1
        this.#read("-") || this.#read("+");
        // 0x1111
        if (this.#read("0x")) {
            this.#readAsLongAs(Character.isHexadecimalIntegerPart);
        } else {
            const leadingPoint = this.#read(".");
            // 1 or 1.1 or 1.1f
            this.#readAsLongAs(Character.isIntegerPart);
            if (leadingPoint === null || this.#read(".")) {
                this.#readAsLongAs(Character.isIntegerPart);
            }
            this.#read("f");
        }
        this.#tokens.push({
            type: TokenType.LiteralNumber,
            value: this.#contents.subarray(start, this.#offset),
        });
        return true;
    }
    #readUntil(value: string) {
        const start = this.#offset;
        const encoded = new TextEncoder().encode(value);
        while (!this.#eof() && !this.#peek(encoded)) {
            this.#offset++;
        }
        return {
            start,
            end: this.#offset,
        };
    }
    #readPunctuator() {
        const punctuators = [
            "...",
            "&&",
            "||",
            "%",
            "!=",
            "::",
            "=",
            "|",
            "/",
            ".",
            "+",
            "-",
            ":",
            "*",
            "{",
            "&",
            "~",
            "}",
            ",",
            "!",
            "<",
            "?",
            ">",
            "[",
            "]",
            '"',
            ";",
            "(",
            ")",
        ].sort((a, b) => b.length - a.length);
        for (const p of punctuators) {
            if (!this.#peek(p)) {
                continue;
            }
            const value = this.#expect(p);
            this.#tokens.push({
                type: TokenType.Punctuator,
                value,
            });
            return true;
        }
        return false;
    }
    /**
     * mandatorily expects for a token
     * @param value string to expect
     */
    #expect(value: string) {
        const result = this.#read(value);
        assert.strict.ok(
            result !== null,
            `${this.#hrPosition()} failed to find token ${value}. next contents are:\n${new TextDecoder().decode(
                this.#contents.subarray(this.#offset, this.#offset + 100)
            )}`
        );
        return result;
    }
    #read(value: string): Uint8Array | null {
        const match = this.#peek(value);
        if (match) {
            this.#offset += match.byteLength;
            return match;
        }
        return null;
    }
    #peek(value: string | Uint8Array, skipByteCount = 0): Uint8Array | null {
        const expected =
            typeof value === "string" ? new TextEncoder().encode(value) : value;
        const remainingBytes =
            this.#contents.byteLength - this.#offset - skipByteCount;
        if (remainingBytes < expected.byteLength) {
            return null;
        }
        for (let i = 0; i < expected.byteLength; i++) {
            if (
                this.#contents[this.#offset + i + skipByteCount] !== expected[i]
            ) {
                return null;
            }
        }
        return this.#contents.subarray(
            this.#offset,
            this.#offset + expected.byteLength
        );
    }
    #hrPosition() {
        let lineNumber = 0;
        for (const byte of this.#contents.subarray(0, this.#offset)) {
            if (Character.isLineBreak(byte)) {
                lineNumber++;
            }
        }
        return `${this.#file}:${lineNumber + 1}:`;
    }
    #readIdentifier() {
        const start = this.#offset;
        while (!this.#eof() && Character.isIdentifierPart(this.#current())) {
            this.#offset++;
        }
        const value = this.#contents.subarray(start, this.#offset);
        this.#tokens.push({
            type: TokenType.Identifier,
            value,
        });
    }
    #charCode(skip = 0) {
        assert.strict.ok(skip >= 0, "unexpected offset");
        const offset = this.#offset + skip;
        const ch = this.#contents[offset];
        assert.strict.ok(typeof ch === "number", "unexpected end of file");
        return ch;
    }
    #current() {
        return this.#charCode(0);
    }
    #eof() {
        return this.#offset >= this.#contents.length;
    }
}
