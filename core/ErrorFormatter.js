"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
const Character_1 = __importDefault(require("./Character"));
function countLineBreaks(contents, maxByteOffset = contents.byteLength) {
    let lineNumber = 0;
    let lineNumberOffset = 0;
    for (const item of contents.subarray(0, maxByteOffset)) {
        if (Character_1.default.isLineBreak(item)) {
            lineNumber++;
            lineNumberOffset = 0;
        }
        else {
            lineNumberOffset++;
        }
    }
    return { lineNumber, lineNumberOffset };
}
function firstLineBreakOffset(contents, desiredStartByteOffset) {
    let i = 0;
    const startByteOffset = Math.min(contents.byteLength, desiredStartByteOffset);
    for (const byte of contents.subarray(startByteOffset)) {
        if (Character_1.default.isLineBreak(byte)) {
            break;
        }
        i++;
    }
    return startByteOffset + i;
}
function lastLineBreakOffset(contents, from) {
    assert_1.default.strict.ok(from <= contents.byteLength - 1);
    let i;
    let ch;
    for (i = 0; i < from; i++) {
        ch = contents[from - i] ?? null;
        assert_1.default.strict.ok(ch !== null, "Unexpected EOF");
        if (Character_1.default.isLineBreak(ch)) {
            break;
        }
    }
    return from - i;
}
class ErrorFormatter {
    #contents;
    #file;
    #offset;
    constructor({ contents, offset, file }) {
        this.#contents = contents;
        this.#file = file;
        this.#offset = offset;
    }
    preview(desiredRewindByteCount = 20) {
        const rewind = lastLineBreakOffset(this.#contents, Math.max(0, this.#offset() - desiredRewindByteCount));
        const slice = this.#contents.subarray(rewind, firstLineBreakOffset(this.#contents, this.#offset() + 10));
        const position = countLineBreaks(this.#contents.subarray(rewind, this.#offset()));
        return {
            position,
            slice
        };
    }
    format(message) {
        const { lineNumber, lineNumberOffset } = countLineBreaks(this.#contents, this.#offset());
        const previewInfo = this.preview(30);
        const previewText = new TextDecoder().decode(previewInfo.slice);
        const finalPreview = previewText.split("\n");
        const position = previewInfo.position;
        finalPreview.splice(position.lineNumber + 1, 0, `${" ".repeat(position.lineNumberOffset)}^ ${message}`);
        return `Error at ${this.#file}:${lineNumber + 1}:${lineNumberOffset}:\n\n\t${message}\n\nDetailed:\n\n${finalPreview.join("\n")}\n\n`;
    }
}
exports.default = ErrorFormatter;
//# sourceMappingURL=ErrorFormatter.js.map