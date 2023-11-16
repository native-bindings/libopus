import assert from "assert";

interface IVariablePosition {
    start: number;
    end: number;
}

export default function mapVariablePositions(value: string) {
    const variables = new Map<string, IVariablePosition>();
    for (let i = 0; i < value.length; i++) {
        if (value.substring(i).startsWith("${")) {
            let j = i;
            while (j < value.length && value[j] !== "}") {
                j++;
            }
            assert.strict.ok(
                value[j] === "}",
                `expected } at ${j} offset of ${value}, but found ${value[j]} instead`
            );
            variables.set(value.substring(i + 2, j), {
                start: i,
                end: j,
            });
            i = j;
        }
    }
    return variables;
}
