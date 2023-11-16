import ErrorFormatter from "./ErrorFormatter";
import Exception from "./Exception";

export interface IUint8ArrayReaderOptions {
    contents: Uint8Array;
    file: string;
}

export default class Uint8ArrayReader {
    readonly #errorFormatter;
    readonly #contents;
    #offset = 0;
    public constructor({ contents, file }: IUint8ArrayReaderOptions) {
        this.#contents = contents;
        this.#errorFormatter = new ErrorFormatter({
            contents,
            file,
            offset: () => this.#offset
        });
    }
    public byteLength() {
        return this.#contents.byteLength;
    }
    public subarray(start: number, end: number) {
        return this.#contents.subarray(start, end);
    }
    public position() {
        return this.#offset;
    }
    /**
     * Validates the current character
     * @param validator function to validate the current character
     * @returns true if the current character is valid according to @param validator, false otherwise
     */
    public validate(validator: (ch: number) => boolean) {
        return validator(this.current());
    }
    public current() {
        const error = this.#errorFormatter.format(`Unexpected EOF`);
        if (this.eof()) {
            throw new Exception(error);
        }
        const ch = this.eof() ? undefined : this.#contents[this.#offset];
        if (typeof ch === "undefined") {
            throw new Exception(error);
        }
        return ch;
    }
    public read(value: string) {
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
    public advance() {
        if (this.eof()) {
            throw new Exception(this.#errorFormatter.format(`Unexpected EOF`));
        }
        this.#offset++;
    }
    /**
     * Keep reading until the reader reaches EOF or @param value is found
     * @param value value that the reader should read until
     */
    public readUntil(value: string) {
        while (!this.eof() && !this.peek(value)) {
            this.#offset++;
        }
    }
    public expect(...oneOfList: string[]) {
        let result: Uint8Array | null = null;
        for (const value of oneOfList) {
            result = this.read(value);
            if (result !== null) {
                break;
            }
        }
        if (result === null) {
            const [value] = oneOfList;
            if (oneOfList.length > 1) {
                throw new Exception(
                    this.#errorFormatter.format(
                        `Expected one of ${oneOfList.join(", ")}`
                    )
                );
            }
            throw new Exception(
                this.#errorFormatter.format(`Expected ${value}`)
            );
        }
        return result;
    }
    public peek(value: string) {
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
        return contents.subarray(
            this.#offset,
            this.#offset + encoded.byteLength
        );
    }
    public eof() {
        return this.#offset >= this.#contents.byteLength;
    }
}
