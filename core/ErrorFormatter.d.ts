export default class ErrorFormatter {
    #private;
    constructor({ contents, offset, file }: {
        contents: Uint8Array;
        file: string;
        offset(): number;
    });
    preview(desiredRewindByteCount?: number): {
        position: {
            lineNumber: number;
            lineNumberOffset: number;
        };
        slice: Uint8Array;
    };
    format(message: string): string;
}
//# sourceMappingURL=ErrorFormatter.d.ts.map