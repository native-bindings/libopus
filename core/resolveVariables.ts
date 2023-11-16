import assert from "assert";
import mapVariablePositions from "./mapVariablePositions";

export default function resolveVariables(
    key: string,
    variables: Map<string, string>,
    initialKey = key
) {
    const initialValue = variables.get(key);
    assert.strict.ok(
        typeof initialValue !== "undefined",
        `variable not found: ${key} - required by ${initialKey}`
    );
    const posMap = mapVariablePositions(initialValue);
    let diff = 0;
    let value = initialValue;
    for (const [name, pos] of posMap.entries()) {
        if (initialKey === name) {
            assert.strict.fail(
                `circular dependency detected: ${name} -> ${initialKey}`
            );
        }
        const dependency = resolveVariables(name, variables, initialKey);
        const newValue =
            value.substring(0, diff + pos.start) +
            dependency +
            value.substring(diff + pos.end + "}".length);
        diff += newValue.length - value.length;
        value = newValue;
    }
    return value;
}
