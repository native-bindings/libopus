"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
function mapVariablePositions(value) {
    const variables = new Map();
    for (let i = 0; i < value.length; i++) {
        if (value.substring(i).startsWith("${")) {
            let j = i;
            while (j < value.length && value[j] !== "}") {
                j++;
            }
            assert_1.default.strict.ok(value[j] === "}", `expected } at ${j} offset of ${value}, but found ${value[j]} instead`);
            variables.set(value.substring(i + 2, j), {
                start: i,
                end: j,
            });
            i = j;
        }
    }
    return variables;
}
exports.default = mapVariablePositions;
//# sourceMappingURL=mapVariablePositions.js.map