"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
const resolveVariables_1 = __importDefault(require("./resolveVariables"));
class PkgConfigFileParser {
    #contents;
    #definitions = new Map();
    #packageInfo = new Map();
    #offset = 0;
    constructor(contents) {
        this.#contents = contents;
    }
    parse() {
        while (!this.#eof()) {
            const identifier = this.#readIdentifier();
            if (this.#read("=")) {
                const value = this.#readUntil("\n");
                this.#definitions.set(identifier, value);
            }
            else if (this.#read(":")) {
                assert_1.default.strict.ok(this.#read(" "), 'expected a whitespace after ":"');
                const value = this.#readUntil("\n");
                this.#packageInfo.set(identifier, value);
            }
            else if (!this.#read("\n") && !this.#read(" ")) {
                assert_1.default.strict.fail(`unexpected token "${this.#current()}" with char code ${this.#current().charCodeAt(0)}`);
            }
        }
        return this.#resolve();
    }
    #resolve() {
        const mergedMap = new Map([...this.#definitions, ...this.#packageInfo]);
        const output = new Map();
        for (const key of mergedMap.keys()) {
            output.set(key, (0, resolveVariables_1.default)(key, mergedMap));
        }
        return output;
    }
    #readUntil(value) {
        assert_1.default.strict.ok(!this.#eof() && value.length === 1);
        const start = this.#offset;
        while (!this.#eof() && this.#current() !== value) {
            this.#offset++;
        }
        const result = this.#contents.substring(start, this.#offset);
        assert_1.default.strict.ok(this.#read(value), `expected ${value} at the end`);
        return result;
    }
    #readIdentifier() {
        const start = this.#offset;
        while (!this.#eof() && /^[0-9a-zA-Z_.]$/.test(this.#current())) {
            this.#offset++;
        }
        return this.#contents.substring(start, this.#offset);
    }
    #read(value) {
        if (this.#peek(value)) {
            this.#offset += value.length;
            return true;
        }
        return false;
    }
    #peek(value) {
        return (this.#contents.substring(this.#offset, this.#offset + value.length) === value);
    }
    #current() {
        return this.#contents.substring(this.#offset, this.#offset + 1);
    }
    #eof() {
        return this.#offset >= this.#contents.length;
    }
}
exports.default = PkgConfigFileParser;
//# sourceMappingURL=PkgConfigFileParser.js.map