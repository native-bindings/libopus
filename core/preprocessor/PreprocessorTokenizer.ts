import Character from "../Character";
import ErrorFormatter from "../ErrorFormatter";
import Exception from "../Exception";
import RangeFactory, { IRange } from "../RangeFactory";
import Uint8ArrayReader, {
    IUint8ArrayReaderOptions,
} from "../Uint8ArrayReader";

export enum PreprocessorTokenType {
    Punctuator,
    Identifier,
    LiteralNumber,
    DirectivePunctuator,
    LineBreak,
    Backslash,
    /**
     * the `value` property should contain just the string literal without the quotes
     */
    LiteralString,
    UnprocessedBlock,
}

export interface IPreprocessorToken {
    type: PreprocessorTokenType;
    value: Uint8Array;
    position: IRange;
}

export default class PreprocessorTokenizer extends Uint8ArrayReader {
    readonly #tokens = new Array<IPreprocessorToken>();
    readonly #errorFormatter;
    readonly #rangeFactory;
    public constructor({ contents, file }: IUint8ArrayReaderOptions) {
        super({ contents, file });
        this.#errorFormatter = new ErrorFormatter({
            contents,
            file,
            offset: () => this.position(),
        });
        this.#rangeFactory = new RangeFactory({
            errorFormatter: this.#errorFormatter,
            position: () => this.position(),
        });
    }
    public tokenize() {
        while (!this.eof()) {
            if (this.peek("/*")) {
                this.readUntil("*/");
                this.expect("*/");
            } else if (this.peek("#")) {
                this.#readDirective();
            } else if (
                this.validate(Character.isWhiteSpace) ||
                this.validate(Character.isLineBreak)
            ) {
                this.advance();
            } else {
                /**
                 * advance on everything else
                 */
                this.readUntil("\n");
            }
        }
        this.#createRawCodeTokens();
        return this.#tokens;
    }
    #createRawCodeTokens() {
        let byteLength: number;
        /**
         * index to add the raw code token
         */
        let addIndex: number;
        const tokens = this.#tokens;
        for (let i = 0; i < tokens.length; i++) {
            const token = tokens[i];
            const nextToken =
                i === tokens.length - 1 ? null : tokens[i + 1] ?? null;
            if (!token) {
                throw new Exception("Expected a token, but it was undefined");
            }
            /**
             * if it's the first token and it's not at the beginning of the file,
             * it means that there is raw code before the first token
             */
            if (i === 0 && token.position.start > 0) {
                tokens.splice(0, 0, {
                    type: PreprocessorTokenType.UnprocessedBlock,
                    value: this.subarray(0, token.position.start),
                    position: {
                        start: 0,
                        end: token.position.start,
                    },
                });
                continue;
            }
            if (nextToken !== null) {
                addIndex = i + 1;
                byteLength = nextToken.position.start - token.position.end;
            } else {
                addIndex = tokens.length;
                byteLength = this.byteLength() - token.position.end;
            }
            /**
             * if the byte length is less than 1, it means that there is no raw code between
             * the tokens or between the last token and EOF
             */
            if (byteLength < 1) {
                continue;
            }
            const end = token.position.end + byteLength;
            const rawCode = this.subarray(token.position.end, end);
            tokens.splice(addIndex, 0, {
                type: PreprocessorTokenType.UnprocessedBlock,
                value: rawCode,
                position: {
                    start: token.position.end,
                    end,
                },
            });
        }
    }
    #readLiteralNumber() {
        const start = this.position();
        while (!this.eof() && this.validate(Character.isIntegerPart)) {
            this.advance();
        }
        if (this.read(".")) {
            while (!this.eof() && this.validate(Character.isIntegerPart)) {
                this.advance();
            }
            this.read("f");
        } else {
            this.read("LU") || this.read("L") || this.read("U");
        }
        const end = this.position();
        this.#tokens.push({
            type: PreprocessorTokenType.LiteralNumber,
            value: this.subarray(start, end),
            position: {
                start,
                end,
            },
        });
    }
    #readLiteralString() {
        this.#rangeFactory.mark();
        this.expect('"');
        const start = this.position();
        while (!this.eof() && !this.peek('"')) {
            if (this.validate(Character.isLineBreak)) {
                throw new Exception(
                    this.#errorFormatter.format(
                        "Unexpected line break in string literal"
                    )
                );
            }
            this.advance();
        }
        const end = this.position();
        this.expect('"');
        const range = this.#rangeFactory.range();
        this.#tokens.push({
            type: PreprocessorTokenType.LiteralString,
            value: this.subarray(start, end),
            position: range,
        });
    }
    #readLineBreak() {
        const start = this.position();
        const result = this.read("\n");
        if (!result) {
            return false;
        }
        this.#tokens.push({
            type: PreprocessorTokenType.LineBreak,
            value: result,
            position: {
                start,
                end: this.position(),
            },
        });
        return true;
    }
    #readBackslash() {
        const start = this.position();
        const result = this.read("\\");
        if (result === null) {
            return false;
        }
        this.#tokens.push({
            type: PreprocessorTokenType.Backslash,
            value: result,
            position: {
                start,
                end: this.position(),
            },
        });
        return true;
    }
    #readDirective() {
        this.#rangeFactory.mark();
        const value = this.expect("#");
        this.#tokens.push({
            type: PreprocessorTokenType.DirectivePunctuator,
            value,
            position: this.#rangeFactory.range(),
        });
        while (!this.eof() && !this.#readLineBreak()) {
            if (this.#readBackslash()) {
                this.readUntil("\n");
                if (!this.#readLineBreak()) {
                    throw new Exception(
                        this.#errorFormatter.format(
                            'Expected line break after "\\"'
                        )
                    );
                }
            } else if (Character.isIdentifierStart(this.current())) {
                this.#readIdentifier();
            } else if (Character.isStringLiteralStart(this.current())) {
                this.#readLiteralString();
            } else if (this.validate(Character.isIdentifierPart)) {
                this.#readLiteralNumber();
            } else {
                /**
                 * lastly, if it's not a punctuator, simply skips the token
                 */
                if (this.#readPunctuator() === null) {
                    this.advance();
                }
            }
        }
    }
    #readPunctuator() {
        const punctuators = [
            "&&",
            "||",
            ">=",
            "<=",
            "==",
            "!=",
            "!",
            "(",
            ")",
            "<",
            ">",
            "/",
            ",",
            "...",
        ].sort((a, b) => b.length - a.length);
        /**
         * Mark position before reading punctuator
         */
        this.#rangeFactory.mark();
        /**
         * Try to read all the punctuators described in the list
         */
        for (const punctuator of punctuators) {
            const result = this.read(punctuator);
            /**
             * In case the current punctuator is not found, continue to the next one
             */
            if (result === null) {
                continue;
            }
            const position = this.#rangeFactory.range();
            const token: IPreprocessorToken = {
                type: PreprocessorTokenType.Punctuator,
                value: result,
                position,
            };
            this.#tokens.push(token);
            return token;
        }
        /**
         * In case a punctuator is found, the mark will be reset by the range() call. In case no
         * punctuator is found, we will reach here. In this case, we need to reset the mark manually
         * to avoid errors when mark() is called again.
         */
        this.#rangeFactory.reset();
        return null;
    }
    #readIdentifier() {
        if (!Character.isIdentifierPart(this.current())) {
            throw new Exception(
                this.#errorFormatter.format(`Expected identifier start`)
            );
        }
        this.#rangeFactory.mark();
        while (!this.eof() && Character.isIdentifierPart(this.current())) {
            this.advance();
        }
        const range = this.#rangeFactory.range();
        this.#tokens.push({
            type: PreprocessorTokenType.Identifier,
            value: this.subarray(range.start, range.end),
            position: range,
        });
    }
}
