import assert from "assert";
import resolveVariables from "./resolveVariables";
import ErrorFormatter from "./ErrorFormatter";

export default class PkgConfigFileParser {
    readonly #contents;
    readonly #definitions = new Map<string, string>();
    readonly #packageInfo = new Map<string, string>();
    readonly #errorFormatter;
    #offset = 0;
    public constructor({ file, contents }: { contents: string; file: string }) {
        this.#contents = contents;
        this.#errorFormatter = new ErrorFormatter({
            contents: new TextEncoder().encode(contents),
            offset: () => this.#offset,
            file,
        });
    }
    public parse(): ReadonlyMap<string, string> {
        while (!this.#eof()) {
            if (this.#read("#")) {
                this.#readUntil("\n");
                continue;
            }
            const identifier = this.#readIdentifier();
            if (this.#read("=")) {
                const value = this.#readUntil("\n");
                this.#definitions.set(identifier, value);
            } else if (this.#read(":")) {
                const value = this.#readUntil("\n");
                this.#packageInfo.set(identifier, value);
            } else if (!this.#read("\n") && !this.#read(" ")) {
                assert.strict.fail(
                    this.#errorFormatter.format(
                        `unexpected token "${this.#current()}" with char code ${this.#current().charCodeAt(
                            0
                        )}`
                    )
                );
            }
        }
        return this.#resolve();
    }
    #resolve() {
        const mergedMap = new Map([...this.#definitions, ...this.#packageInfo]);
        const output = new Map<string, string>();
        for (const key of mergedMap.keys()) {
            output.set(key, resolveVariables(key, mergedMap));
        }
        return output;
    }
    #readUntil(value: string) {
        assert.strict.ok(!this.#eof() && value.length === 1);
        const start = this.#offset;
        while (!this.#eof() && this.#current() !== value) {
            this.#offset++;
        }
        const result = this.#contents.substring(start, this.#offset);
        assert.strict.ok(this.#read(value), `expected ${value} at the end`);
        return result;
    }
    #readIdentifier() {
        const start = this.#offset;
        while (!this.#eof() && /^[0-9a-zA-Z_.]$/.test(this.#current())) {
            this.#offset++;
        }
        return this.#contents.substring(start, this.#offset);
    }
    #read(value: string) {
        if (this.#peek(value)) {
            this.#offset += value.length;
            return true;
        }
        return false;
    }
    #peek(value: string) {
        return (
            this.#contents.substring(
                this.#offset,
                this.#offset + value.length
            ) === value
        );
    }
    #current() {
        return this.#contents.substring(this.#offset, this.#offset + 1);
    }
    #eof() {
        return this.#offset >= this.#contents.length;
    }
}
