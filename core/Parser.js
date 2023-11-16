"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
const Tokenizer_1 = require("./Tokenizer");
function tokenTypeToString(type) {
    switch (type) {
        case Tokenizer_1.TokenType.Identifier:
            return "Identifier";
        case Tokenizer_1.TokenType.LiteralNumber:
            return "LiteralNumber";
        case Tokenizer_1.TokenType.LiteralString:
            return "LiteralString";
        case Tokenizer_1.TokenType.Punctuator:
            return "Punctuator";
    }
}
class Parser {
    #tokens;
    #enumDefinitions = new Array();
    #offset = 0;
    constructor(tokens) {
        this.#tokens = tokens;
        this.#peek;
    }
    parse() {
        while (!this.#eof()) {
            if (this.#peek("typedef")) {
                this.#readTypedef();
            }
            else {
                this.#read(null);
            }
        }
        return {
            enumDefinitions: this.#enumDefinitions,
        };
    }
    #readIdentifier() {
        const token = this.#expect(null);
        assert_1.default.strict.ok(token.type === Tokenizer_1.TokenType.Identifier, `Expected identifier but got ${tokenTypeToString(token.type)} instead`);
        return token;
    }
    #readEnum() {
        this.#expect("enum");
        let name;
        if (this.#current().type === Tokenizer_1.TokenType.Identifier) {
            name = this.#readIdentifier();
        }
        else {
            name = null;
        }
        this.#expect("{");
        const values = new Array();
        while (!this.#eof() && !this.#peek("}")) {
            const name = this.#readIdentifier();
            if (this.#read("=")) {
                while (!this.#eof() && !this.#peek("}") && !this.#peek(",")) {
                    this.#read(null);
                }
            }
            values.push({
                name: new TextDecoder().decode(name.value),
            });
            if (!this.#read(",")) {
                break;
            }
        }
        this.#expect("}");
        return { name, values };
    }
    #readTypedef() {
        this.#expect("typedef");
        if (!this.#peek("enum")) {
            return;
        }
        const enumDefinition = this.#readEnum();
        if (enumDefinition.name !== null) {
            console.warn(`enum ${new TextDecoder().decode(enumDefinition.name.value)} defined inside a typedef should not have a name`);
        }
        const typeDefName = this.#readIdentifier();
        this.#enumDefinitions.push({
            name: new TextDecoder().decode(typeDefName.value),
            values: enumDefinition.values,
        });
        this.#expect(";");
    }
    #expect(value) {
        const result = this.#read(value);
        assert_1.default.strict.ok(result !== null, `expected ${value}, but got ${this.#current().value} instead`);
        return result;
    }
    #peek(value) {
        const token = this.#current();
        if (value === new TextDecoder().decode(token.value)) {
            return token;
        }
        return null;
    }
    #read(value) {
        const token = this.#current();
        if (value === null || value === new TextDecoder().decode(token.value)) {
            this.#offset++;
            return token;
        }
        return null;
    }
    #current() {
        const token = this.#tokens[this.#offset];
        assert_1.default.strict.ok(typeof token !== "undefined", `Expected token at offset ${this.#offset} but got undefined`);
        return token;
    }
    #eof() {
        return this.#offset === this.#tokens.length;
    }
}
exports.default = Parser;
//# sourceMappingURL=Parser.js.map