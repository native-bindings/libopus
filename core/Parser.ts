import assert from "assert";
import { IToken, TokenType } from "./Tokenizer";

function tokenTypeToString(type: TokenType) {
    switch (type) {
        case TokenType.Identifier:
            return "Identifier";
        case TokenType.LiteralNumber:
            return "LiteralNumber";
        case TokenType.LiteralString:
            return "LiteralString";
        case TokenType.Punctuator:
            return "Punctuator";
    }
}

export interface IEnumDefinitionValue {
    name: string;
}

export interface IEnumDefinition {
    name: string;
    values: IEnumDefinitionValue[];
}

export default class Parser {
    readonly #tokens;
    readonly #enumDefinitions = new Array<IEnumDefinition>();
    #offset = 0;
    public constructor(tokens: ReadonlyArray<IToken>) {
        this.#tokens = tokens;
        this.#peek;
    }
    public parse() {
        while (!this.#eof()) {
            if (this.#peek("typedef")) {
                this.#readTypedef();
            } else {
                this.#read(null);
            }
        }
        return {
            enumDefinitions: this.#enumDefinitions,
        };
    }
    #readIdentifier() {
        const token = this.#expect(null);
        assert.strict.ok(
            token.type === TokenType.Identifier,
            `Expected identifier but got ${tokenTypeToString(
                token.type
            )} instead`
        );
        return token;
    }
    #readEnum() {
        this.#expect("enum");
        let name: IToken | null;
        if (this.#current().type === TokenType.Identifier) {
            name = this.#readIdentifier();
        } else {
            name = null;
        }
        this.#expect("{");
        const values = new Array<IEnumDefinitionValue>();
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
            console.warn(
                `enum ${new TextDecoder().decode(
                    enumDefinition.name.value
                )} defined inside a typedef should not have a name`
            );
        }
        const typeDefName = this.#readIdentifier();
        this.#enumDefinitions.push({
            name: new TextDecoder().decode(typeDefName.value),
            values: enumDefinition.values,
        });
        this.#expect(";");
    }
    #expect(value: string | null) {
        const result = this.#read(value);
        assert.strict.ok(
            result !== null,
            `expected ${value}, but got ${this.#current().value} instead`
        );
        return result;
    }
    #peek(value: string) {
        const token = this.#current();
        if (value === new TextDecoder().decode(token.value)) {
            return token;
        }
        return null;
    }
    #read(value: string | null) {
        const token = this.#current();
        if (value === null || value === new TextDecoder().decode(token.value)) {
            this.#offset++;
            return token;
        }
        return null;
    }
    #current() {
        const token = this.#tokens[this.#offset];
        assert.strict.ok(
            typeof token !== "undefined",
            `Expected token at offset ${this.#offset} but got undefined`
        );
        return token;
    }
    #eof() {
        return this.#offset === this.#tokens.length;
    }
}
