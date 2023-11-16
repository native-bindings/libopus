"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const ava_1 = __importDefault(require("ava"));
const mapVariablePositions_1 = __importDefault(require("./mapVariablePositions"));
const resolveVariables_1 = __importDefault(require("./resolveVariables"));
(0, ava_1.default)("resolveVariables: it should resolve variables of pkg config files", (t) => {
    t.deepEqual((0, mapVariablePositions_1.default)("hello ${a}, ${b} and ${c}!"), new Map([
        ["a", { start: 6, end: 9 }],
        ["b", { start: 12, end: 15 }],
        ["c", { start: 21, end: 24 }]
    ]));
    t.deepEqual((0, resolveVariables_1.default)("final", new Map([
        ["final", "hello ${a}, ${b} and ${c}!"],
        ["a", "${prefix} ${name}"],
        ["name", "Queiroz"],
        ["prefix", "Mr."],
        ["b", "${prefix} ${name}"],
        ["c", "${prefix} ${name}"]
    ])), "hello Mr. Queiroz, Mr. Queiroz and Mr. Queiroz!");
});
//# sourceMappingURL=resolveVariables.spec.js.map