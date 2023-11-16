"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const ErrorFormatter_1 = __importDefault(require("./ErrorFormatter"));
const Exception_1 = __importDefault(require("./Exception"));
class Uint8ArrayReader {
    #errorFormatter;
    #contents;
    #offset = 0;
    constructor({ contents, file }) {
        this.#contents = contents;
        this.#errorFormatter = new ErrorFormatter_1.default({
            contents,
            file,
            offset: () => this.#offset
        });
    }
    byteLength() {
        return this.#contents.byteLength;
    }
    subarray(start, end) {
        return this.#contents.subarray(start, end);
    }
    position() {
        return this.#offset;
    }
    /**
     * Validates the current character
     * @param validator function to validate the current character
     * @returns true if the current character is valid according to @param validator, false otherwise
     */
    validate(validator) {
        return validator(this.current());
    }
    current() {
        const error = this.#errorFormatter.format(`Unexpected EOF`);
        if (this.eof()) {
            throw new Exception_1.default(error);
        }
        const ch = this.eof() ? undefined : this.#contents[this.#offset];
        if (typeof ch === "undefined") {
            throw new Exception_1.default(error);
        }
        return ch;
    }
    read(value) {
        const match = this.peek(value);
        if (match === null) {
            return null;
        }
        this.#offset += match.byteLength;
        return match;
    }
    /**
     * Advance the reader to the next character
     */
    advance() {
        if (this.eof()) {
            throw new Exception_1.default(this.#errorFormatter.format(`Unexpected EOF`));
        }
        this.#offset++;
    }
    /**
     * Keep reading until the reader reaches EOF or @param value is found
     * @param value value that the reader should read until
     */
    readUntil(value) {
        while (!this.eof() && !this.peek(value)) {
            this.#offset++;
        }
    }
    expect(...oneOfList) {
        let result = null;
        for (const value of oneOfList) {
            result = this.read(value);
            if (result !== null) {
                break;
            }
        }
        if (result === null) {
            const [value] = oneOfList;
            if (oneOfList.length > 1) {
                throw new Exception_1.default(this.#errorFormatter.format(`Expected one of ${oneOfList.join(", ")}`));
            }
            throw new Exception_1.default(this.#errorFormatter.format(`Expected ${value}`));
        }
        return result;
    }
    peek(value) {
        if (this.eof()) {
            return null;
        }
        const encoded = new TextEncoder().encode(value);
        const contents = this.#contents;
        const remaining = contents.byteLength - this.#offset;
        if (encoded.byteLength > remaining) {
            return null;
        }
        for (let i = 0; i < encoded.byteLength; i++) {
            if (encoded[i] !== contents[this.#offset + i]) {
                return null;
            }
        }
        return contents.subarray(this.#offset, this.#offset + encoded.byteLength);
    }
    eof() {
        return this.#offset >= this.#contents.byteLength;
    }
}
exports.default = Uint8ArrayReader;
//# sourceMappingURL=Uint8ArrayReader.js.map