import { IRange } from "../RangeFactory";
import Uint8ArrayReader, { IUint8ArrayReaderOptions } from "../Uint8ArrayReader";
export declare enum PreprocessorTokenType {
    Punctuator = 0,
    Identifier = 1,
    LiteralNumber = 2,
    DirectivePunctuator = 3,
    LineBreak = 4,
    Backslash = 5,
    /**
     * the `value` property should contain just the string literal without the quotes
     */
    LiteralString = 6,
    UnprocessedBlock = 7
}
export interface IPreprocessorToken {
    type: PreprocessorTokenType;
    value: Uint8Array;
    position: IRange;
}
export default class PreprocessorTokenizer extends Uint8ArrayReader {
    #private;
    constructor({ contents, file }: IUint8ArrayReaderOptions);
    tokenize(): IPreprocessorToken[];
}
//# sourceMappingURL=PreprocessorTokenizer.d.ts.map