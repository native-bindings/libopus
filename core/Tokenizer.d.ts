export declare enum TokenType {
    LiteralNumber = 0,
    LiteralString = 1,
    Identifier = 2,
    Punctuator = 3
}
export interface IToken {
    type: TokenType;
    value: Uint8Array;
}
export default class Tokenizer {
    #private;
    constructor({ contents, file, }: {
        contents: Uint8Array;
        file: string;
    });
    tokenize(): IToken[];
}
//# sourceMappingURL=Tokenizer.d.ts.map