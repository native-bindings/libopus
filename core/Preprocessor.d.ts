export declare enum PreprocessorNodeType {
    IfDefined = 0,
    IfNotDefined = 1,
    If = 2,
    EndIf = 3,
    Else = 4,
    Include = 5,
    Define = 6,
    Undefine = 7,
    Error = 8,
    Warning = 9,
    Line = 10,
    Pragma = 11,
    Extension = 12,
    Version = 13
}
export interface IPreprocessorDefineNode {
    type: PreprocessorNodeType.Define;
    arguments: Uint8Array[];
    value: Uint8Array;
    name: Uint8Array;
}
export type PreprocessorNode = IPreprocessorDefineNode;
export default class Preprocessor {
    #private;
    constructor({ contents, file }: {
        contents: Uint8Array;
        file: string;
    });
    preprocess(): void;
}
//# sourceMappingURL=Preprocessor.d.ts.map