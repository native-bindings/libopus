"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
const mapVariablePositions_1 = __importDefault(require("./mapVariablePositions"));
function resolveVariables(key, variables, initialKey = key) {
    const initialValue = variables.get(key);
    assert_1.default.strict.ok(typeof initialValue !== "undefined", `variable not found: ${key} - required by ${initialKey}`);
    const posMap = (0, mapVariablePositions_1.default)(initialValue);
    let diff = 0;
    let value = initialValue;
    for (const [name, pos] of posMap.entries()) {
        if (initialKey === name) {
            assert_1.default.strict.fail(`circular dependency detected: ${name} -> ${initialKey}`);
        }
        const dependency = resolveVariables(name, variables, initialKey);
        const newValue = value.substring(0, diff + pos.start) +
            dependency +
            value.substring(diff + pos.end + "}".length);
        diff += newValue.length - value.length;
        value = newValue;
    }
    return value;
}
exports.default = resolveVariables;
//# sourceMappingURL=resolveVariables.js.map