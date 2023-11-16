import { IToken } from "./Tokenizer";
export interface IEnumDefinitionValue {
    name: string;
}
export interface IEnumDefinition {
    name: string;
    values: IEnumDefinitionValue[];
}
export default class Parser {
    #private;
    constructor(tokens: ReadonlyArray<IToken>);
    parse(): {
        enumDefinitions: IEnumDefinition[];
    };
}
//# sourceMappingURL=Parser.d.ts.map