export interface IUint8ArrayReaderOptions {
    contents: Uint8Array;
    file: string;
}
export default class Uint8ArrayReader {
    #private;
    constructor({ contents, file }: IUint8ArrayReaderOptions);
    byteLength(): number;
    subarray(start: number, end: number): Uint8Array;
    position(): number;
    /**
     * Validates the current character
     * @param validator function to validate the current character
     * @returns true if the current character is valid according to @param validator, false otherwise
     */
    validate(validator: (ch: number) => boolean): boolean;
    current(): number;
    read(value: string): Uint8Array | null;
    /**
     * Advance the reader to the next character
     */
    advance(): void;
    /**
     * Keep reading until the reader reaches EOF or @param value is found
     * @param value value that the reader should read until
     */
    readUntil(value: string): void;
    expect(...oneOfList: string[]): Uint8Array;
    peek(value: string): Uint8Array | null;
    eof(): boolean;
}
//# sourceMappingURL=Uint8ArrayReader.d.ts.map