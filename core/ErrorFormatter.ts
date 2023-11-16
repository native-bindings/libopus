import assert from "assert";
import Character from "./Character";

function countLineBreaks(
    contents: Uint8Array,
    maxByteOffset: number = contents.byteLength
) {
    let lineNumber = 0;
    let lineNumberOffset = 0;
    for (const item of contents.subarray(0, maxByteOffset)) {
        if (Character.isLineBreak(item)) {
            lineNumber++;
            lineNumberOffset = 0;
        } else {
            lineNumberOffset++;
        }
    }
    return { lineNumber, lineNumberOffset };
}

function firstLineBreakOffset(
    contents: Uint8Array,
    desiredStartByteOffset: number
) {
    let i = 0;
    const startByteOffset = Math.min(
        contents.byteLength,
        desiredStartByteOffset
    );
    for (const byte of contents.subarray(startByteOffset)) {
        if (Character.isLineBreak(byte)) {
            break;
        }
        i++;
    }
    return startByteOffset + i;
}

function lastLineBreakOffset(contents: Uint8Array, from: number) {
    assert.strict.ok(from <= contents.byteLength - 1);
    let i: number;
    let ch: number | null;
    for (i = 0; i < from; i++) {
        ch = contents[from - i] ?? null;
        assert.strict.ok(ch !== null, "Unexpected EOF");
        if (Character.isLineBreak(ch)) {
            break;
        }
    }
    return from - i;
}

export default class ErrorFormatter {
    readonly #contents;
    readonly #file;
    readonly #offset;
    public constructor({
        contents,
        offset,
        file
    }: {
        contents: Uint8Array;
        file: string;
        offset(): number;
    }) {
        this.#contents = contents;
        this.#file = file;
        this.#offset = offset;
    }
    public preview(desiredRewindByteCount = 20) {
        const rewind = lastLineBreakOffset(
            this.#contents,
            Math.max(0, this.#offset() - desiredRewindByteCount)
        );
        const slice = this.#contents.subarray(
            rewind,
            firstLineBreakOffset(this.#contents, this.#offset() + 10)
        );
        const position = countLineBreaks(
            this.#contents.subarray(rewind, this.#offset())
        );
        return {
            position,
            slice
        };
    }
    public format(message: string) {
        const { lineNumber, lineNumberOffset } = countLineBreaks(
            this.#contents,
            this.#offset()
        );
        const previewInfo = this.preview(30);
        const previewText = new TextDecoder().decode(previewInfo.slice);
        const finalPreview = previewText.split("\n");
        const position = previewInfo.position;
        finalPreview.splice(
            position.lineNumber + 1,
            0,
            `${" ".repeat(position.lineNumberOffset)}^ ${message}`
        );
        return `Error at ${this.#file}:${
            lineNumber + 1
        }:${lineNumberOffset}:\n\n\t${message}\n\nDetailed:\n\n${finalPreview.join(
            "\n"
        )}\n\n`;
    }
}
