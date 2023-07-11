import assert from "assert";

const startNumberRegularExpression = /^(\-|[0-9]){1}/;

type Value = IValueLiteralNumber | IValueLiteralString;

interface IValueLiteralNumber {
    type: "literalNumber";
    isNegative: boolean;
    value: string;
}

interface IValueLiteralString {
    type: "literalString";
    value: string;
}

export type MacroDefinition =
    | {
          type: "valueMacro";
          key: string;
          value: Value | null;
      }
    | {
          type: "functionMacro";
          key: string;
          args: string[];
          contents: string;
      };

export default class MacroReader {
    #index = 0;
    readonly #line;
    public constructor(line: string) {
        this.#line = line;
    }
    public read(): MacroDefinition {
        this.#expect("#");
        assert.strict.ok(this.#readIdentifier() === "define");
        this.#readWhiteSpaces();
        const key = this.#readIdentifier();
        this.#readWhiteSpaces();
        if (this.#match("(")) {
            const args = new Array<string>();
            if (!this.#match(")")) {
                do {
                    args.push(this.#readIdentifier());
                } while (!this.#eof() && !this.#match(")") && this.#match(","));
            }
            this.#readWhiteSpaces();
            const contents = this.#remaining();
            this.#match(contents);
            return {
                type: "functionMacro",
                key,
                args,
                contents,
            };
        }
        return {
            type: "valueMacro",
            key,
            value: this.#readValue(),
        };
    }
    #readValue(): Value | null {
        if (this.#remaining().startsWith('"')) {
            return this.#readLiteralString();
        }
        if (startNumberRegularExpression.test(this.#remaining())) {
            return this.#readLiteralNumber();
        }
        return null;
    }
    #readLiteralNumber(): IValueLiteralNumber {
        const isNegative = this.#match("-");
        const startIndex = this.#index;
        while (
            !this.#eof() &&
            startNumberRegularExpression.test(this.#remaining())
        ) {
            this.#advance();
        }
        assert.strict.ok(startIndex !== this.#index);
        return {
            type: "literalNumber",
            isNegative,
            value: this.#line.substring(startIndex, this.#index),
        };
    }
    #readLiteralString(): IValueLiteralString {
        assert.strict.ok(this.#expect('"'));
        const valueStartIndex = this.#index;
        while (!this.#eof() && !this.#match('"')) {
            this.#advance();
        }
        assert.strict.ok(this.#expect('"'));
        return {
            type: "literalString",
            value: this.#line.substring(valueStartIndex, this.#index),
        };
    }
    /**
     * @deprecated just create a damn C or C++ parser written in TypeScript
     */
    #readWhiteSpaces() {
        while (this.#remaining().startsWith(" ")) this.#advance();
    }
    #match(value: string) {
        if (this.#remaining().startsWith(value)) {
            this.#index += value.length;
            return true;
        }
        return false;
    }
    #eof() {
        return this.#index === this.#line.length;
    }
    #remaining() {
        assert.strict.ok(!this.#eof());
        return this.#line.substring(this.#index);
    }
    #advance() {
        assert.strict.ok(!this.#eof());
        this.#index++;
    }
    #expect(value: string) {
        assert.strict.ok(this.#remaining().startsWith(value));
        this.#index += value.length;
    }
    #readIdentifier() {
        const startIndex = this.#index;
        while (!this.#eof() && /^[a-zA-Z0-9_]{1}/.test(this.#remaining())) {
            this.#advance();
        }
        assert.strict.ok(
            startIndex !== this.#index,
            "failed to read identifier"
        );
        return this.#line.substring(startIndex, this.#index);
    }
}
