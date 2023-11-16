"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.TokenType = void 0;
const assert_1 = __importDefault(require("assert"));
const Character_1 = __importDefault(require("./Character"));
var TokenType;
(function (TokenType) {
    TokenType[TokenType["LiteralNumber"] = 0] = "LiteralNumber";
    TokenType[TokenType["LiteralString"] = 1] = "LiteralString";
    TokenType[TokenType["Identifier"] = 2] = "Identifier";
    TokenType[TokenType["Punctuator"] = 3] = "Punctuator";
})(TokenType || (exports.TokenType = TokenType = {}));
class Tokenizer {
    #contents;
    #file;
    #tokens = new Array();
    #offset;
    constructor({ contents, file, }) {
        this.#contents = contents;
        this.#offset = 0;
        this.#file = file;
    }
    tokenize() {
        while (!this.#eof()) {
            const ch = this.#current();
            if (Character_1.default.isTab(ch) ||
                Character_1.default.isLineBreak(ch) ||
                Character_1.default.isWhiteSpace(ch)) {
                this.#offset++;
            }
            else if (ch === 35) {
                this.#expect("#");
                while (!this.#eof() && !this.#peek("\n")) {
                    if (this.#peek("\\")) {
                        this.#readUntil("\n");
                        this.#expect("\n");
                    }
                    else {
                        this.#offset++;
                    }
                }
            }
            else if (this.#peek("//")) {
                this.#expect("//");
                while (!this.#eof() && !this.#peek("\n")) {
                    this.#offset++;
                }
                this.#expect("\n");
            }
            else if (this.#read("/*")) {
                while (!this.#eof() && !this.#peek("*/")) {
                    this.#offset++;
                }
                this.#expect("*/");
            }
            else if (Character_1.default.isIdentifierStart(ch)) {
                this.#readIdentifier();
            }
            else if (this.#isLiteralNumberStart()) {
                this.#readLiteralNumber();
            }
            else {
                assert_1.default.strict.ok(this.#readPunctuator(), `${this.#hrPosition()} unexpected character (${ch}) ${new TextDecoder().decode(new Uint8Array([ch]))}:\n${new TextDecoder().decode(this.#contents.subarray(this.#offset, this.#offset + 100))}`);
            }
        }
        return this.#tokens;
    }
    #isLiteralNumberStart() {
        let ch;
        /**
         * if current character is a plus sign, negative sign or a dot, set `ch` to the next character,
         * so it can be checked by the end of the method if it's whether an integer part or not (0-9).
         */
        if (this.#peek(".") || this.#peek("+") || this.#peek("-")) {
            ch = this.#charCode(1);
        }
        else {
            /**
             * in case there's no sign or dot, then do the last check by checking if the current `ch` is an integer part.
             */
            ch = this.#current();
        }
        /**
         * here we check the character after the sign or dot is a sign, or if the current character is a sign
         */
        return Character_1.default.isIntegerPart(ch);
    }
    #readAsLongAs(validate) {
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
            this.#readAsLongAs(Character_1.default.isHexadecimalIntegerPart);
        }
        else {
            const leadingPoint = this.#read(".");
            // 1 or 1.1 or 1.1f
            this.#readAsLongAs(Character_1.default.isIntegerPart);
            if (leadingPoint === null || this.#read(".")) {
                this.#readAsLongAs(Character_1.default.isIntegerPart);
            }
            this.#read("f");
        }
        this.#tokens.push({
            type: TokenType.LiteralNumber,
            value: this.#contents.subarray(start, this.#offset),
        });
        return true;
    }
    #readUntil(value) {
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
    #expect(value) {
        const result = this.#read(value);
        assert_1.default.strict.ok(result !== null, `${this.#hrPosition()} failed to find token ${value}. next contents are:\n${new TextDecoder().decode(this.#contents.subarray(this.#offset, this.#offset + 100))}`);
        return result;
    }
    #read(value) {
        const match = this.#peek(value);
        if (match) {
            this.#offset += match.byteLength;
            return match;
        }
        return null;
    }
    #peek(value, skipByteCount = 0) {
        const expected = typeof value === "string" ? new TextEncoder().encode(value) : value;
        const remainingBytes = this.#contents.byteLength - this.#offset - skipByteCount;
        if (remainingBytes < expected.byteLength) {
            return null;
        }
        for (let i = 0; i < expected.byteLength; i++) {
            if (this.#contents[this.#offset + i + skipByteCount] !== expected[i]) {
                return null;
            }
        }
        return this.#contents.subarray(this.#offset, this.#offset + expected.byteLength);
    }
    #hrPosition() {
        let lineNumber = 0;
        for (const byte of this.#contents.subarray(0, this.#offset)) {
            if (Character_1.default.isLineBreak(byte)) {
                lineNumber++;
            }
        }
        return `${this.#file}:${lineNumber + 1}:`;
    }
    #readIdentifier() {
        const start = this.#offset;
        while (!this.#eof() && Character_1.default.isIdentifierPart(this.#current())) {
            this.#offset++;
        }
        const value = this.#contents.subarray(start, this.#offset);
        this.#tokens.push({
            type: TokenType.Identifier,
            value,
        });
    }
    #charCode(skip = 0) {
        assert_1.default.strict.ok(skip >= 0, "unexpected offset");
        const offset = this.#offset + skip;
        const ch = this.#contents[offset];
        assert_1.default.strict.ok(typeof ch === "number", "unexpected end of file");
        return ch;
    }
    #current() {
        return this.#charCode(0);
    }
    #eof() {
        return this.#offset >= this.#contents.length;
    }
}
exports.default = Tokenizer;
//# sourceMappingURL=Tokenizer.js.map