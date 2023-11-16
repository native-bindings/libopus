import { IPreprocessorToken } from "./PreprocessorTokenizer";
export declare enum PreprocessorNodeType {
    Identifier = 0,
    UnaryExpression = 1,
    LogicalExpression = 2,
    FunctionCallExpression = 3,
    UnprocessedBlock = 4,
    UndefDirective = 5,
    ErrorDirective = 6,
    IncludeDirective = 7,
    DefineMacroDirective = 8,
    EndIfDirective = 9,
    LiteralString = 10,
    LiteralNumber = 11,
    ElseDirective = 12,
    IfNotDefinedDirective = 13,
    IfDirective = 14,
    IfDefinedDirective = 15
}
interface INodeUnprocessedBlock {
    type: PreprocessorNodeType.UnprocessedBlock;
    value: Uint8Array;
}
interface INodeUndefDirective {
    type: PreprocessorNodeType.UndefDirective;
    name: INodeIdentifier;
}
interface INodeErrorDirective {
    type: PreprocessorNodeType.ErrorDirective;
    value: Uint8Array;
}
interface INodeEndIfDirective {
    type: PreprocessorNodeType.EndIfDirective;
}
interface INodeElseDirective {
    type: PreprocessorNodeType.ElseDirective;
}
interface INodeIdentifier {
    type: PreprocessorNodeType.Identifier;
    value: Uint8Array;
}
interface INodeUnaryExpression {
    type: PreprocessorNodeType.UnaryExpression;
    operator: Uint8Array;
    expression: PreprocessorNode;
}
type Expression = INodeLiteralNumber | INodeIdentifier | INodeFunctionCallExpression | INodeLogicalExpression;
interface INodeFunctionCallExpression {
    type: PreprocessorNodeType.FunctionCallExpression;
    name: Expression;
    args: INodeIdentifier[];
}
interface INodeLogicalExpression {
    type: PreprocessorNodeType.LogicalExpression;
    left: PreprocessorNode;
    operator: Uint8Array;
    right: PreprocessorNode;
}
/**
 * works for both #ifndef and #ifdef
 */
interface INodeConditionalDirective {
    type: PreprocessorNodeType.IfNotDefinedDirective | PreprocessorNodeType.IfDefinedDirective | PreprocessorNodeType.IfDirective;
    condition: PreprocessorNode;
    body: PreprocessorNode[];
    alternative: PreprocessorNode[];
}
interface INodeDefineMacroDirective {
    type: PreprocessorNodeType.DefineMacroDirective;
    name: INodeIdentifier;
    arguments: INodeIdentifier[];
    value: Uint8Array | null;
    variadic: boolean;
}
interface INodeIncludeDirective {
    type: PreprocessorNodeType.IncludeDirective;
    value: Uint8Array;
    local: boolean;
}
interface INodeLiteralString {
    type: PreprocessorNodeType.LiteralString;
    value: Uint8Array;
}
interface INodeLiteralNumber {
    type: PreprocessorNodeType.LiteralNumber;
    value: Uint8Array;
}
export type PreprocessorNode = INodeIdentifier | INodeLiteralString | INodeDefineMacroDirective | INodeConditionalDirective | INodeUnprocessedBlock | INodeErrorDirective | INodeUnaryExpression | INodeEndIfDirective | INodeIncludeDirective | INodeElseDirective | INodeLiteralNumber | INodeLogicalExpression | INodeFunctionCallExpression | INodeUndefDirective;
export interface IPreprocessorParserOptions {
    file: string;
    contents: Uint8Array;
    tokens: IPreprocessorToken[];
}
export declare function decodePreprocessorNode(node: PreprocessorNode): unknown;
/**
 * Find holes between the items, and create "filler items" to fill the holes
 */
export declare function addUnprocessedSlices<T>({ tokens, contents, getNewItem, getItemRange }: {
    tokens: T[];
    contents: Uint8Array;
    getItemRange: (value: T) => {
        start: number;
        end: number;
    };
    getNewItem: (value: Uint8Array) => T;
}): void;
export default class PreprocessorParser {
    #private;
    constructor(options: IPreprocessorParserOptions);
    parse(): PreprocessorNode[];
}
export {};
//# sourceMappingURL=PreprocessorParser.d.ts.map