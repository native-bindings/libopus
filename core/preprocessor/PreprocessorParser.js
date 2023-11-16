"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.addUnprocessedSlices = exports.decodePreprocessorNode = exports.PreprocessorNodeType = void 0;
const ErrorFormatter_1 = __importDefault(require("../ErrorFormatter"));
const Exception_1 = __importDefault(require("../Exception"));
const compareBuffer_1 = __importDefault(require("../compareBuffer"));
const PreprocessorTokenizer_1 = require("./PreprocessorTokenizer");
const isTokenImmediatelyAfter_1 = __importDefault(require("./isTokenImmediatelyAfter"));
var PreprocessorNodeType;
(function (PreprocessorNodeType) {
    PreprocessorNodeType[PreprocessorNodeType["Identifier"] = 0] = "Identifier";
    PreprocessorNodeType[PreprocessorNodeType["UnaryExpression"] = 1] = "UnaryExpression";
    PreprocessorNodeType[PreprocessorNodeType["LogicalExpression"] = 2] = "LogicalExpression";
    PreprocessorNodeType[PreprocessorNodeType["FunctionCallExpression"] = 3] = "FunctionCallExpression";
    PreprocessorNodeType[PreprocessorNodeType["UnprocessedBlock"] = 4] = "UnprocessedBlock";
    PreprocessorNodeType[PreprocessorNodeType["UndefDirective"] = 5] = "UndefDirective";
    PreprocessorNodeType[PreprocessorNodeType["ErrorDirective"] = 6] = "ErrorDirective";
    PreprocessorNodeType[PreprocessorNodeType["IncludeDirective"] = 7] = "IncludeDirective";
    PreprocessorNodeType[PreprocessorNodeType["DefineMacroDirective"] = 8] = "DefineMacroDirective";
    PreprocessorNodeType[PreprocessorNodeType["EndIfDirective"] = 9] = "EndIfDirective";
    PreprocessorNodeType[PreprocessorNodeType["LiteralString"] = 10] = "LiteralString";
    PreprocessorNodeType[PreprocessorNodeType["LiteralNumber"] = 11] = "LiteralNumber";
    PreprocessorNodeType[PreprocessorNodeType["ElseDirective"] = 12] = "ElseDirective";
    PreprocessorNodeType[PreprocessorNodeType["IfNotDefinedDirective"] = 13] = "IfNotDefinedDirective";
    PreprocessorNodeType[PreprocessorNodeType["IfDirective"] = 14] = "IfDirective";
    PreprocessorNodeType[PreprocessorNodeType["IfDefinedDirective"] = 15] = "IfDefinedDirective";
})(PreprocessorNodeType || (exports.PreprocessorNodeType = PreprocessorNodeType = {}));
function decodeText(value) {
    return new TextDecoder().decode(value);
}
// export type DecodePreprocessorNodes<T> = T extends PreprocessorNode ? {
//     [K in keyof T]: T[K] extends Uint8Array ? string : T[K] extends PreprocessorNode ? DecodePreprocessorNodes<T> : T[K]
// } : never
// type DecodedPreprocessorNode = DecodePreprocessorNodes<PreprocessorNode>;
function decodePreprocessorNode(node) {
    switch (node.type) {
        default:
            // @ts-expect-error this is a hack to make sure that all node types are handled
            throw new Exception_1.default(`Unhandled node type: ${node.type}`);
        case PreprocessorNodeType.ErrorDirective:
            return {
                ...node,
                value: decodeText(node.value)
            };
        case PreprocessorNodeType.UndefDirective:
            return {
                ...node,
                name: decodePreprocessorNode(node.name)
            };
        case PreprocessorNodeType.LiteralNumber:
            return {
                ...node,
                value: decodeText(node.value)
            };
        case PreprocessorNodeType.LiteralString:
            return {
                ...node,
                value: decodeText(node.value)
            };
        case PreprocessorNodeType.IncludeDirective:
            return {
                ...node,
                file: decodeText(node.value)
            };
        case PreprocessorNodeType.FunctionCallExpression:
            return {
                ...node,
                name: decodePreprocessorNode(node.name),
                args: node.args.map((arg) => decodePreprocessorNode(arg))
            };
        case PreprocessorNodeType.UnaryExpression:
            return {
                ...node,
                expression: decodePreprocessorNode(node.expression),
                operator: decodeText(node.operator)
            };
        case PreprocessorNodeType.EndIfDirective:
        case PreprocessorNodeType.ElseDirective:
            return node;
        case PreprocessorNodeType.Identifier:
            return {
                ...node,
                value: decodeText(node.value)
            };
        case PreprocessorNodeType.DefineMacroDirective:
            return {
                ...node,
                name: {
                    ...node.name,
                    value: decodeText(node.name.value)
                },
                arguments: node.arguments.map((arg) => ({
                    ...arg,
                    value: decodeText(arg.value)
                })),
                value: node.value ? decodeText(node.value) : null
            };
        case PreprocessorNodeType.IfNotDefinedDirective:
        case PreprocessorNodeType.IfDefinedDirective:
        case PreprocessorNodeType.IfDirective:
            return {
                ...node,
                condition: decodePreprocessorNode(node.condition),
                body: decodePreprocessorNodes(node.body),
                alternative: decodePreprocessorNodes(node.alternative)
            };
        case PreprocessorNodeType.UnprocessedBlock:
            return {
                ...node,
                value: decodeText(node.value)
            };
        case PreprocessorNodeType.LogicalExpression:
            return {
                ...node,
                left: decodePreprocessorNode(node.left),
                operator: decodeText(node.operator),
                right: decodePreprocessorNode(node.right)
            };
    }
}
exports.decodePreprocessorNode = decodePreprocessorNode;
function decodePreprocessorNodes(nodes) {
    return nodes.map((node) => decodePreprocessorNode(node));
}
/**
 * Find holes between the items, and create "filler items" to fill the holes
 */
function addUnprocessedSlices({ tokens, contents, getNewItem, getItemRange }) {
    let byteLength;
    /**
     * index to add the raw code token
     */
    let addIndex;
    for (let i = 0; i < tokens.length; i++) {
        const token = tokens[i];
        const nextToken = i === tokens.length - 1 ? null : tokens[i + 1] ?? null;
        if (!token) {
            throw new Exception_1.default("Expected a token, but it was undefined");
        }
        const nextTokenRange = getItemRange(token);
        const currentRange = getItemRange(token);
        /**
         * if it's the first token and it's not at the beginning of the file,
         * it means that there is raw code before the first token
         */
        if (i === 0 && currentRange.start > 0) {
            tokens.splice(0, 0, getNewItem(contents.subarray(0, currentRange.start)));
            continue;
        }
        if (nextToken !== null) {
            addIndex = i + 1;
            byteLength = nextTokenRange.start - currentRange.end;
        }
        else {
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
exports.addUnprocessedSlices = addUnprocessedSlices;
class PreprocessorParser {
    #tokens;
    #contents;
    #nodes = new Array();
    #errorFormatter;
    #offset = 0;
    constructor(options) {
        const { file, tokens, contents } = options;
        this.#errorFormatter = new ErrorFormatter_1.default({
            contents,
            file,
            offset: () => this.#current().position.start
        });
        this.#contents = contents;
        this.#tokens = tokens.filter((t) => 
        // filter out whitespace tokens
        !(0, compareBuffer_1.default)(t.value, new TextEncoder().encode(" ")));
    }
    parse() {
        while (!this.#eof()) {
            const node = this.#parseCurrent();
            if (node === null) {
                continue;
            }
            this.#nodes.push(node);
        }
        return this.#nodes;
    }
    #parseCurrent() {
        if (this.#peek("#")) {
            return this.#parseDirective();
        }
        else if (this.#current().type === PreprocessorTokenizer_1.PreprocessorTokenType.UnprocessedBlock) {
            const token = this.#advance();
            return {
                type: PreprocessorNodeType.UnprocessedBlock,
                value: token.value
            };
        }
        this.#advance();
        return null;
    }
    #parseEndIfDirective() {
        this.#expect("endif");
        return {
            type: PreprocessorNodeType.EndIfDirective
        };
    }
    #parseLiteralString() {
        const token = this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.LiteralString);
        return {
            type: PreprocessorNodeType.LiteralString,
            value: token.value
        };
    }
    #parseDirective() {
        this.#expect("#");
        const token = this.#current();
        switch (new TextDecoder().decode(token.value)) {
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
                this.#advanceDirective();
                return {
                    type: PreprocessorNodeType.ElseDirective
                };
            case "error":
                const start = this.#current().position.start;
                const finalToken = this.#advanceDirective();
                if (finalToken === null) {
                    throw new Exception_1.default(this.#errorFormatter.format(`Expected token after #error directive`));
                }
                return {
                    type: PreprocessorNodeType.ErrorDirective,
                    value: this.#contents.subarray(start, finalToken.position.end)
                };
        }
        if (this.#test("ifndef", "ifdef", "if", "elif")) {
        }
        else if (this.#peek("define")) {
        }
        else if (this.#peek("endif")) {
        }
        else if (this.#read("else")) {
        }
        else if (this.#peek("include")) {
            return this.#parseIncludeDirective();
        }
        else if (this.#peek("undef")) {
            return this.#parseUndefDirective();
        }
        else if (this.#peek("error")) {
            const start = this.#current().position.start;
            this.#advanceDirective();
            const end = this.#current().position.start;
            return {
                type: PreprocessorNodeType.ErrorDirective,
                value: this.#contents.subarray(start, end)
            };
        }
        throw new Exception_1.default(this.#errorFormatter.format(`Expected unknown directive`));
    }
    #parseUndefDirective() {
        this.#expect("undef");
        const name = this.#parseIdentifier();
        return {
            type: PreprocessorNodeType.UndefDirective,
            name
        };
    }
    #parseIncludeDirective() {
        this.#expect("include");
        const local = this.#current().type === PreprocessorTokenizer_1.PreprocessorTokenType.LiteralString;
        let value;
        if (local) {
            value = this.#parseLiteralString().value;
        }
        else {
            this.#expect("<");
            const start = this.#current().position.start;
            let lastToken = null;
            while (!this.#eof() && !this.#peek(">")) {
                lastToken = this.#advance();
            }
            if (lastToken === null) {
                throw new Exception_1.default(this.#errorFormatter.format(`Expected token after #include directive`));
            }
            value = this.#contents.subarray(start, lastToken.position.end);
            this.#expect(">");
        }
        this.#advanceDirective();
        return {
            type: PreprocessorNodeType.IncludeDirective,
            value,
            local
        };
    }
    /**
     * Advance the directive contents until a line break is reached. it can handle
     * directive backslashes and more. the final line break is not consumed. For that
     * reason, the caller must consume the line break with #expectTokenType(PreprocessorTokenType.LineBreak)
     */
    #advanceDirective() {
        let lastToken = this.#eof() ? null : this.#current();
        while (!this.#eof() && !this.#peek("\n")) {
            if (this.#readTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.Backslash)) {
                this.#readUntil("\n");
                this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.LineBreak);
                continue;
            }
            lastToken = this.#advance();
        }
        return lastToken;
    }
    #parseDefineMacroDirective() {
        this.#expect("define");
        const name = this.#parseIdentifier();
        const defineArguments = new Array();
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
        let value;
        if (this.#offset > offset) {
            const lastDirectiveToken = this.#tokenAt(this.#offset - 1);
            value = this.#contents.subarray(this.#tokenAt(offset).position.start, lastDirectiveToken.position.end);
        }
        else {
            value = null;
        }
        this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.LineBreak);
        return {
            variadic,
            type: PreprocessorNodeType.DefineMacroDirective,
            arguments: defineArguments,
            value,
            name
        };
    }
    #parseIdentifier() {
        const token = this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.Identifier);
        return {
            type: PreprocessorNodeType.Identifier,
            value: token.value
        };
    }
    #parseLiteralNumber() {
        const token = this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.LiteralNumber);
        return {
            type: PreprocessorNodeType.LiteralNumber,
            value: token.value
        };
    }
    #parsePrimaryExpression() {
        const token = this.#current();
        let result;
        switch (token.type) {
            case PreprocessorTokenizer_1.PreprocessorTokenType.LiteralNumber:
                result = this.#parseLiteralNumber();
                break;
            case PreprocessorTokenizer_1.PreprocessorTokenType.Identifier:
                result = this.#parseIdentifier();
                break;
            default:
                throw new Exception_1.default(this.#errorFormatter.format(`Unexpected token`));
        }
        if (this.#read("(")) {
            const passedArgs = new Array();
            while (!this.#eof() && !this.#peek(")")) {
                passedArgs.push(this.#parseIdentifier());
                if (!this.#read(",")) {
                    break;
                }
            }
            this.#expect(")");
            result = {
                type: PreprocessorNodeType.FunctionCallExpression,
                name: result,
                args: passedArgs
            };
        }
        return result;
    }
    #parseLogicalExpression() {
        const expression = this.#parseUnaryExpression();
        let result = expression;
        if (this.#peek("&&")) {
            const operator = this.#expectEither("&&");
            const right = this.#parseUnaryExpression();
            if (right === null) {
                throw new Exception_1.default(this.#errorFormatter.format("Failed to read right part of logical expression"));
            }
            result = {
                type: PreprocessorNodeType.LogicalExpression,
                left: result,
                operator: operator.value,
                right
            };
        }
        return result;
    }
    #parseUnaryExpression() {
        if (this.#peek("!")) {
            const operator = this.#expect("!");
            const expression = this.#parseUnaryExpression();
            return {
                operator: operator.value,
                type: PreprocessorNodeType.UnaryExpression,
                expression
            };
        }
        return this.#parsePrimaryExpression();
    }
    #parseConditionalDirective() {
        let condition;
        if (this.#read("ifdef")) {
            condition = this.#parseIdentifier();
        }
        else if (this.#read("ifndef")) {
            condition = this.#parseIdentifier();
        }
        else if (this.#read("if") || this.#read("elif")) {
            condition = this.#parseLogicalExpression();
        }
        else {
            throw new Exception_1.default(this.#errorFormatter.format("Expected #ifdef, #ifndef or #if"));
        }
        /**
         * finish te reading the directive in case any comments are present or so
         */
        this.#advanceDirective();
        this.#expectTokenType(PreprocessorTokenizer_1.PreprocessorTokenType.LineBreak);
        const body = new Array();
        const alternative = new Array();
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
                        throw new Exception_1.default(`Cannot have more than one #else directive`);
                    }
                    currentList = alternative;
                    break;
                default:
                    currentList.push(node);
            }
        }
        const node = {
            type: PreprocessorNodeType.IfNotDefinedDirective,
            condition,
            body,
            alternative
        };
        return node;
    }
    #readImmediatelyAfter(value) {
        const previous = this.#offset > 0 ? this.#tokenAt(this.#offset - 1) : null;
        /**
         * if no previous token exists, then the token cannot be immediately after
         */
        if (!previous) {
            return null;
        }
        const match = this.#peek(value);
        if (!match || !(0, isTokenImmediatelyAfter_1.default)(match, previous)) {
            return null;
        }
        return this.#expect(value);
    }
    #readUntil(value) {
        while (!this.#eof() && !this.#peek(value)) {
            this.#advance();
        }
    }
    #readTokenType(type) {
        const current = this.#current();
        if (current.type !== type) {
            return null;
        }
        this.#advance();
        return current;
    }
    #tokenAt(offset) {
        if (offset < 0 && offset > this.#tokens.length - 1) {
            throw new Exception_1.default(this.#errorFormatter.format(`Token offset ${offset} is out of range`));
        }
        const token = this.#tokens[offset];
        if (typeof token === "undefined") {
            throw new Exception_1.default(this.#errorFormatter.format(`Token offset ${offset} is undefined`));
        }
        return token;
    }
    #expectEither(...possibilities) {
        if (this.#eof()) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected one of ${possibilities.join(", ")}, but reached the end of the file`));
        }
        if (possibilities.length < 1) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected at least one possibility`));
        }
        for (const p of possibilities) {
            const result = this.#read(p);
            if (result) {
                return result;
            }
        }
        throw new Exception_1.default(this.#errorFormatter.format(`Expected one of ${possibilities.join(", ")}, but current value is ${this.#current().value}`));
    }
    #expectTokenType(type) {
        if (this.#eof()) {
            throw new Exception_1.default(`Expected token type ${type}, but reached the end of the file`);
        }
        const token = this.#readTokenType(type);
        if (token === null) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected token type ${type}, but got ${this.#current().type}`));
        }
        return token;
    }
    #expect(value) {
        const token = this.#read(value);
        if (token === null) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected ${value}, but got ${new TextDecoder().decode(this.#current().value)}`));
        }
        return token;
    }
    #read(value) {
        const token = this.#peek(value);
        if (token === null) {
            return null;
        }
        this.#advance();
        return token;
    }
    #test(...value) {
        for (const v of value) {
            const token = this.#peek(v);
            if (token !== null) {
                return token;
            }
        }
        return null;
    }
    #peek(value, skip = 0) {
        if (this.#eof()) {
            return null;
        }
        const token = this.#tokens[this.#offset + skip];
        if (typeof token === "undefined") {
            return null;
        }
        if (!(0, compareBuffer_1.default)(token.value, new TextEncoder().encode(value))) {
            return null;
        }
        return token;
    }
    #advance() {
        if (this.#eof()) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected a token, but reached the end of the file`));
        }
        const current = this.#current();
        this.#offset++;
        return current;
    }
    #current() {
        const token = this.#tokens[this.#offset];
        if (!token) {
            throw new Exception_1.default(this.#errorFormatter.format(`Expected a token, but it was undefined`));
        }
        return token;
    }
    #eof() {
        return this.#offset >= this.#tokens.length;
    }
}
exports.default = PreprocessorParser;
//# sourceMappingURL=PreprocessorParser.js.map