import Character from "../Character";
import ErrorFormatter from "../ErrorFormatter";
import Exception from "../Exception";
import compareBuffer from "../compareBuffer";
import {
    IPreprocessorToken,
    PreprocessorTokenType,
} from "./PreprocessorTokenizer";
import isTokenImmediatelyAfter from "./isTokenImmediatelyAfter";

export enum PreprocessorNodeType {
    Identifier,
    LogicalExpression,
    UnaryExpression,
    BinaryExpression,
    UnprocessedBlock,
    UndefDirective,
    ErrorDirective,
    IncludeDirective,
    PragmaDirective,
    DefineMacroDirective,
    EndIfDirective,
    LiteralString,
    LiteralNumber,
    ElseDirective,
    WarningDirective,
    IfNotDefinedDirective,
    IfDirective,
    IfDefinedDirective,
}

interface INodePragmaDirective {
    type: PreprocessorNodeType.PragmaDirective;
    value: Uint8Array;
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
    expression: PreprocessorExpressionNode;
}

interface INodeBinaryExpression {
    type: PreprocessorNodeType.BinaryExpression;
    left: PreprocessorExpressionNode;
    operator: Uint8Array;
    right: PreprocessorExpressionNode;
}

export type PreprocessorExpressionNode =
    | INodeLiteralNumber
    | INodeIdentifier
    | INodeLogicalExpression
    | INodeBinaryExpression
    | INodeUnaryExpression
    | INodeLiteralString;

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
    type:
        | PreprocessorNodeType.IfNotDefinedDirective
        | PreprocessorNodeType.IfDefinedDirective
        | PreprocessorNodeType.IfDirective;
    condition: PreprocessorNode;
    body: PreprocessorNode[];
    alternative: PreprocessorNode[];
}

export interface INodeDefineMacroDirective {
    type: PreprocessorNodeType.DefineMacroDirective;
    name: INodeIdentifier;
    arguments: INodeIdentifier[];
    value: Uint8Array | null;
    variadic: boolean;
}

interface INodeWarningDirective {
    type: PreprocessorNodeType.WarningDirective;
    message: INodeLiteralString;
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

export type PreprocessorNode =
    | INodeIdentifier
    | INodeLiteralString
    | INodeDefineMacroDirective
    | INodeConditionalDirective
    | INodeUnprocessedBlock
    | INodeErrorDirective
    | INodeBinaryExpression
    | INodeUnaryExpression
    | INodeEndIfDirective
    | INodeIncludeDirective
    | INodeWarningDirective
    | INodeElseDirective
    | INodeLiteralNumber
    | INodeLogicalExpression
    | INodeUndefDirective
    | INodePragmaDirective;

export interface IPreprocessorParserOptions {
    file: string;
    contents: Uint8Array;
    tokens: IPreprocessorToken[];
}

function decodeText(value: Uint8Array) {
    return new TextDecoder().decode(value);
}

export function decodePreprocessorNode(node: PreprocessorNode): unknown {
    switch (node.type) {
        default:
            // @ts-expect-error this is a hack to make sure that all node types are handled
            throw new Exception(`Unhandled node type: ${node.type}`);
        case PreprocessorNodeType.PragmaDirective:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.ErrorDirective:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.UndefDirective:
            return {
                ...node,
                name: decodePreprocessorNode(node.name),
            };
        case PreprocessorNodeType.LiteralNumber:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.LiteralString:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.IncludeDirective:
            return {
                ...node,
                file: decodeText(node.value),
            };
        case PreprocessorNodeType.WarningDirective:
            return {
                ...node,
                file: decodeText(node.message.value),
            };
        case PreprocessorNodeType.BinaryExpression:
            return {
                ...node,
                left: decodePreprocessorNode(node.left),
                operator: decodeText(node.operator),
                right: decodePreprocessorNode(node.right),
            };
        case PreprocessorNodeType.UnaryExpression:
            return {
                ...node,
                expression: decodePreprocessorNode(node.expression),
                operator: decodeText(node.operator),
            };
        case PreprocessorNodeType.EndIfDirective:
        case PreprocessorNodeType.ElseDirective:
            return node;
        case PreprocessorNodeType.Identifier:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.DefineMacroDirective:
            return {
                ...node,
                name: {
                    ...node.name,
                    value: decodeText(node.name.value),
                },
                arguments: node.arguments.map((arg) => ({
                    ...arg,
                    value: decodeText(arg.value),
                })),
                value: node.value ? decodeText(node.value) : null,
            };
        case PreprocessorNodeType.IfNotDefinedDirective:
        case PreprocessorNodeType.IfDefinedDirective:
        case PreprocessorNodeType.IfDirective:
            return {
                ...node,
                condition: decodePreprocessorNode(node.condition),
                body: decodePreprocessorNodes(node.body),
                alternative: decodePreprocessorNodes(node.alternative),
            };
        case PreprocessorNodeType.UnprocessedBlock:
            return {
                ...node,
                value: decodeText(node.value),
            };
        case PreprocessorNodeType.LogicalExpression:
            return {
                ...node,
                left: decodePreprocessorNode(node.left),
                operator: decodeText(node.operator),
                right: decodePreprocessorNode(node.right),
            };
    }
}

function decodePreprocessorNodes(nodes: PreprocessorNode[]): unknown {
    return nodes.map((node) => decodePreprocessorNode(node));
}

/**
 * Find holes between the items, and create "filler items" to fill the holes
 */
export function addUnprocessedSlices<T>({
    tokens,
    contents,
    getNewItem,
    getItemRange,
}: {
    tokens: T[];
    contents: Uint8Array;
    getItemRange: (value: T) => { start: number; end: number };
    getNewItem: (value: Uint8Array) => T;
}) {
    let byteLength: number;
    /**
     * index to add the raw code token
     */
    let addIndex: number;
    for (let i = 0; i < tokens.length; i++) {
        const token = tokens[i];
        const nextToken =
            i === tokens.length - 1 ? null : tokens[i + 1] ?? null;
        if (!token) {
            throw new Exception("Expected a token, but it was undefined");
        }
        const nextTokenRange = getItemRange(token);
        const currentRange = getItemRange(token);
        /**
         * if it's the first token and it's not at the beginning of the file,
         * it means that there is raw code before the first token
         */
        if (i === 0 && currentRange.start > 0) {
            tokens.splice(
                0,
                0,
                getNewItem(contents.subarray(0, currentRange.start))
            );
            continue;
        }
        if (nextToken !== null) {
            addIndex = i + 1;
            byteLength = nextTokenRange.start - currentRange.end;
        } else {
            addIndex = tokens.length;
            byteLength = contents.byteLength - currentRange.end;
        }
        /**
         * if the byte length is less than 1, it means that there is no raw code between
         * the tokens or between the last token and EOF
         */
        if (byteLength < 1) {
            continue;
        }
        const end = currentRange.end + byteLength;
        const rawCode = contents.subarray(currentRange.end, end);
        tokens.splice(addIndex, 0, getNewItem(rawCode));
    }
}

export default class PreprocessorParser {
    readonly #tokens: IPreprocessorToken[];
    readonly #contents;
    readonly #nodes = new Array<PreprocessorNode>();
    readonly #errorFormatter;
    #offset = 0;
    public constructor(options: IPreprocessorParserOptions) {
        const { file, tokens, contents } = options;
        this.#errorFormatter = new ErrorFormatter({
            contents,
            file,
            offset: () => this.#current().position.start,
        });
        this.#contents = contents;
        this.#tokens = Array.from(tokens);
        this.#simplifyDirectiveTokens();
    }

    public parse() {
        while (!this.#eof()) {
            const node = this.#parseCurrent();
            if (node === null) {
                continue;
            }
            this.#nodes.push(node);
        }
        return this.#nodes;
    }

    #simplifyDirectiveTokens() {
        while (!this.#eof()) {
            if (
                !this.#readTokenType(PreprocessorTokenType.DirectivePunctuator)
            ) {
                this.#advance();
                continue;
            }
            while (this.#read("\n") === null) {
                /**
                 * remove whitespace-only tokens
                 */
                if (this.#current().value.every(Character.isWhiteSpace)) {
                    this.#tokens.splice(this.#offset, 1);
                    continue;
                }
                /**
                 * remove backslash and line break tokens except for the last one to
                 * avoid having to deal with weird backslashes in the middle of the directive.
                 */
                if (this.#current().type === PreprocessorTokenType.Backslash) {
                    /**
                     * remove backslash token
                     */
                    this.#tokens.splice(this.#offset, 1);
                    /**
                     * after the backslash, read until we reach a line break
                     */
                    this.#readUntil("\n");
                    /**
                     * remove the line break token
                     */
                    this.#tokens.splice(this.#offset, 1);
                    continue;
                }
                this.#advance();
            }
        }
        /**
         * set to 0 to start from the beginning
         */
        this.#offset = 0;
    }

    #parseCurrent(): PreprocessorNode | null {
        if (this.#peek("#")) {
            return this.#parseDirective();
        } else if (
            this.#current().type === PreprocessorTokenType.UnprocessedBlock
        ) {
            const token = this.#advance();
            return {
                type: PreprocessorNodeType.UnprocessedBlock,
                value: token.value,
            };
        }
        this.#advance();
        return null;
    }

    #parseEndIfDirective(): INodeEndIfDirective {
        this.#expect("endif");
        this.#parseDirectiveEnd();
        return {
            type: PreprocessorNodeType.EndIfDirective,
        };
    }

    #parseLiteralString(): INodeLiteralString {
        const token = this.#expectTokenType(
            PreprocessorTokenType.LiteralString
        );
        return {
            type: PreprocessorNodeType.LiteralString,
            value: token.value,
        };
    }

    #parseDirective(): PreprocessorNode {
        this.#expect("#");
        const token = this.#current();
        switch (new TextDecoder().decode(token.value)) {
            case "include":
                return this.#parseIncludeDirective();
            case "pragma": {
                // skip directive name
                this.#parseIdentifier();
                const start = this.#current().position.start;
                const end = this.#parseDirectiveEnd().position.end;
                return {
                    type: PreprocessorNodeType.PragmaDirective,
                    value: this.#contents.subarray(start, end),
                };
            }
            case "undef":
                return this.#parseUndefDirective();
            case "ifndef":
            case "ifdef":
            case "if":
            case "elif":
                return this.#parseConditionalDirective();
            case "define":
                return this.#parseDefineMacroDirective();
            case "endif":
                return this.#parseEndIfDirective();
            case "else":
                this.#parseDirectiveEnd();
                return {
                    type: PreprocessorNodeType.ElseDirective,
                };
            case "warning":
                // skip directive name
                this.#parseIdentifier();
                const value = this.#parseLiteralString();
                /**
                 * finish directive reading
                 */
                this.#parseDirectiveEnd();
                return {
                    type: PreprocessorNodeType.WarningDirective,
                    message: value,
                };
            case "error":
                const start = this.#current().position.start;
                const finalToken = this.#parseDirectiveEnd();
                return {
                    type: PreprocessorNodeType.ErrorDirective,
                    value: this.#contents.subarray(
                        start,
                        finalToken.position.end
                    ),
                };
        }
        throw new Exception(
            this.#errorFormatter.format(`Unknown directive: >${token.value}<`)
        );
    }

    #parseUndefDirective(): INodeUndefDirective {
        this.#expect("undef");
        const name = this.#parseIdentifier();
        this.#parseDirectiveEnd();
        return {
            type: PreprocessorNodeType.UndefDirective,
            name,
        };
    }

    #parseIncludeDirective(): INodeIncludeDirective {
        this.#expect("include");
        const local =
            this.#current().type === PreprocessorTokenType.LiteralString;
        let value: Uint8Array;
        if (local) {
            value = this.#parseLiteralString().value;
        } else {
            this.#expect("<");
            const start = this.#current().position.start;
            let lastToken: IPreprocessorToken | null = null;
            while (!this.#eof() && !this.#peek(">")) {
                lastToken = this.#advance();
            }
            if (lastToken === null) {
                throw new Exception(
                    this.#errorFormatter.format(
                        `Expected token after #include directive`
                    )
                );
            }
            value = this.#contents.subarray(start, lastToken.position.end);
            this.#expect(">");
        }
        this.#parseDirectiveEnd();
        return {
            type: PreprocessorNodeType.IncludeDirective,
            value,
            local,
        };
    }

    #parseDirectiveEnd() {
        const lastDirectiveToken = this.#advanceDirective();
        this.#expectTokenType(PreprocessorTokenType.LineBreak);
        return lastDirectiveToken;
    }

    /**
     * Advance the directive contents until a line break is reached. it can handle
     * directive backslashes and more. the final line break is not consumed. For that
     * reason, the caller must consume the line break with #expectTokenType(PreprocessorTokenType.LineBreak)
     */
    #advanceDirective() {
        if (this.#eof()) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected to advance directive, but reached the end of the file`
                )
            );
        }
        let lastToken = this.#current();
        while (!this.#eof() && !this.#peek("\n")) {
            lastToken = this.#advance();
        }
        return lastToken;
    }

    #parseDefineMacroDirective(): INodeDefineMacroDirective {
        this.#expect("define");
        const name = this.#parseIdentifier();
        const defineArguments = new Array<INodeIdentifier>();
        let variadic = false;
        if (this.#readImmediatelyAfter("(")) {
            while (!this.#eof() && !this.#peek(")")) {
                /**
                 * force ... to be the last argument
                 */
                if (this.#read("...")) {
                    variadic = true;
                    break;
                }
                defineArguments.push(this.#parseIdentifier());
                if (!this.#read(",")) {
                    break;
                }
            }
            this.#expect(")");
        }
        const offset = this.#offset;
        this.#advanceDirective();
        let value: Uint8Array | null;
        if (this.#offset > offset) {
            const lastDirectiveToken = this.#tokenAt(this.#offset - 1);
            value = this.#contents.subarray(
                this.#tokenAt(offset).position.start,
                lastDirectiveToken.position.end
            );
        } else {
            value = null;
        }
        this.#expectTokenType(PreprocessorTokenType.LineBreak);
        return {
            variadic,
            type: PreprocessorNodeType.DefineMacroDirective,
            arguments: defineArguments,
            value,
            name,
        };
    }

    #parseIdentifier(): INodeIdentifier {
        const token = this.#expectTokenType(PreprocessorTokenType.Identifier);
        return {
            type: PreprocessorNodeType.Identifier,
            value: token.value,
        };
    }

    #parseLiteralNumber(): INodeLiteralNumber {
        const token = this.#expectTokenType(
            PreprocessorTokenType.LiteralNumber
        );
        return {
            type: PreprocessorNodeType.LiteralNumber,
            value: token.value,
        };
    }

    #parsePrimaryExpression(): PreprocessorExpressionNode {
        const token = this.#current();
        let result: PreprocessorNode;
        switch (token.type) {
            case PreprocessorTokenType.LiteralNumber:
                result = this.#parseLiteralNumber();
                break;
            case PreprocessorTokenType.Identifier:
                result = this.#parseIdentifier();
                break;
            default:
                throw new Exception(
                    this.#errorFormatter.format(`Unexpected token`)
                );
        }
        return result;
    }

    #parseLogicalExpression(): PreprocessorExpressionNode {
        const expression = this.#parseUnaryExpression();
        for (const operator of ["&&", "||"]) {
            if (!this.#peek(operator)) {
                continue;
            }
            const token = this.#expect(operator);
            const right = this.#parseLogicalExpression();
            if (right === null) {
                throw new Exception(
                    this.#errorFormatter.format(
                        "Failed to read right part of logical expression"
                    )
                );
            }
            return {
                type: PreprocessorNodeType.LogicalExpression,
                left: expression,
                operator: token.value,
                right,
            };
        }
        const binaryOperators = [">=", "<=", "==", "!=", ">", "<"];
        for (const operator of binaryOperators) {
            const token = this.#read(operator);
            if (token === null) {
                continue;
            }
            const right = this.#parseUnaryExpression();
            return {
                type: PreprocessorNodeType.BinaryExpression,
                left: expression,
                operator: token.value,
                right,
            };
        }
        return expression;
    }

    #parseUnaryExpression(): PreprocessorExpressionNode {
        if (this.#read("(")) {
            const result = this.#parseLogicalExpression();
            this.#expect(")");
            return result;
        }
        const unaryOperators = ["!", "defined"];
        for (const operator of unaryOperators) {
            if (!this.#peek(operator)) {
                continue;
            }
            const token = this.#expect(operator);
            const expression = this.#parseLogicalExpression();
            return {
                operator: token.value,
                type: PreprocessorNodeType.UnaryExpression,
                expression,
            };
        }
        return this.#parsePrimaryExpression();
    }

    #parseConditionalDirective() {
        let condition: PreprocessorNode;
        if (this.#read("ifdef")) {
            condition = this.#parseIdentifier();
        } else if (this.#read("ifndef")) {
            condition = this.#parseIdentifier();
        } else if (this.#read("if") || this.#read("elif")) {
            condition = this.#parseLogicalExpression();
        } else {
            throw new Exception(
                this.#errorFormatter.format("Expected #ifdef, #ifndef or #if")
            );
        }

        /**
         * finish te reading the directive in case any comments are present or so
         */
        this.#advanceDirective();
        this.#expectTokenType(PreprocessorTokenType.LineBreak);

        const body = new Array<PreprocessorNode>();
        const alternative = new Array<PreprocessorNode>();

        let currentList = body;
        let ended = false;

        while (!this.#eof() && !ended) {
            const node = this.#parseCurrent();
            if (node === null) {
                continue;
            }
            switch (node.type) {
                case PreprocessorNodeType.EndIfDirective:
                    ended = true;
                    break;
                case PreprocessorNodeType.ElseDirective:
                    if (currentList === alternative) {
                        throw new Exception(
                            `Cannot have more than one #else directive`
                        );
                    }
                    currentList = alternative;
                    break;
                default:
                    currentList.push(node);
            }
        }

        const node: INodeConditionalDirective = {
            type: PreprocessorNodeType.IfNotDefinedDirective,
            condition,
            body,
            alternative,
        };

        return node;
    }

    #readImmediatelyAfter(value: string) {
        const previous =
            this.#offset > 0 ? this.#tokenAt(this.#offset - 1) : null;
        /**
         * if no previous token exists, then the token cannot be immediately after
         */
        if (!previous) {
            return null;
        }
        const match = this.#peek(value);
        if (!match || !isTokenImmediatelyAfter(match, previous)) {
            return null;
        }
        return this.#expect(value);
    }

    #readUntil(value: string) {
        while (!this.#eof() && !this.#peek(value)) {
            this.#advance();
        }
        if (this.#eof()) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected ${value}, but reached the end of the file`
                )
            );
        }
    }

    #readTokenType(type: PreprocessorTokenType) {
        const current = this.#current();
        if (current.type !== type) {
            return null;
        }
        this.#advance();
        return current;
    }

    #tokenAt(offset: number) {
        if (offset < 0 && offset > this.#tokens.length - 1) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Token offset ${offset} is out of range`
                )
            );
        }
        const token = this.#tokens[offset];
        if (typeof token === "undefined") {
            throw new Exception(
                this.#errorFormatter.format(
                    `Token offset ${offset} is undefined`
                )
            );
        }
        return token;
    }

    // #expectEither(...possibilities: string[]) {
    //     if (this.#eof()) {
    //         throw new Exception(
    //             this.#errorFormatter.format(
    //                 `Expected one of ${possibilities.join(
    //                     ", "
    //                 )}, but reached the end of the file`
    //             )
    //         );
    //     }
    //     if (possibilities.length < 1) {
    //         throw new Exception(
    //             this.#errorFormatter.format(`Expected at least one possibility`)
    //         );
    //     }
    //     for (const p of possibilities) {
    //         const result = this.#read(p);
    //         if (result) {
    //             return result;
    //         }
    //     }
    //     throw new Exception(
    //         this.#errorFormatter.format(
    //             `Expected one of ${possibilities.join(
    //                 ", "
    //             )}, but current value is ${this.#current().value}`
    //         )
    //     );
    // }

    #expectTokenType(type: PreprocessorTokenType) {
        if (this.#eof()) {
            throw new Exception(
                `Expected token type ${type}, but reached the end of the file`
            );
        }
        const token = this.#readTokenType(type);
        if (token === null) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected token type ${type}, but got ${
                        this.#current().type
                    }`
                )
            );
        }
        return token;
    }

    #expect(value: string) {
        const token = this.#read(value);
        if (token === null) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected ${value}, but got ${new TextDecoder().decode(
                        this.#current().value
                    )}`
                )
            );
        }
        return token;
    }

    #read(value: string) {
        const token = this.#peek(value);
        if (token === null) {
            return null;
        }
        this.#advance();
        return token;
    }

    // #test(...value: string[]) {
    //     for (const v of value) {
    //         const token = this.#peek(v);
    //         if (token !== null) {
    //             return token;
    //         }
    //     }
    //     return null;
    // }

    #peek(value: string, skip = 0) {
        if (this.#eof()) {
            return null;
        }
        const token = this.#tokens[this.#offset + skip];
        if (typeof token === "undefined") {
            return null;
        }
        if (!compareBuffer(token.value, new TextEncoder().encode(value))) {
            return null;
        }
        return token;
    }

    #advance() {
        if (this.#eof()) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected a token, but reached the end of the file`
                )
            );
        }
        const current = this.#current();
        this.#offset++;
        return current;
    }

    #current() {
        const token = this.#tokens[this.#offset];
        if (!token) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Expected a token, but it was undefined`
                )
            );
        }
        return token;
    }

    #eof() {
        return this.#offset >= this.#tokens.length;
    }
}
