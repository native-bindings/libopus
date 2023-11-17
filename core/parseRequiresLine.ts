import assert from "assert";
import ErrorFormatter from "./ErrorFormatter";

export interface IRequirement {
    name: string;
    version: string | null;
    operator: string | null;
}

export default function parseRequiresLine({
    file,
    value,
}: {
    value: string;
    file: string;
}) {
    const slices = value.split(" ");
    let requiredVersion: string | null = null;
    let requireName: string | null = null;
    let operator: string | null = null;
    let i: number;
    const requirements = new Map<string, IRequirement>();
    const contents = new TextEncoder().encode(value);
    for (i = 0; i < slices.length; i++) {
        const errorFormatter = new ErrorFormatter({
            contents,
            offset: () => i,
            file,
        });
        operator = null;
        requiredVersion = null;
        requireName = slices[i++] ?? null;
        assert.strict.ok(
            requireName !== null,
            errorFormatter.format(`missing require name: ${value}`)
        );
        const nextItem = slices[i];
        if (nextItem === ">=") {
            i++;
            operator = nextItem;
            requiredVersion = slices[++i] ?? null;
            assert.strict.ok(
                requiredVersion === null,
                errorFormatter.format(
                    `missing required version after the operator: ${value}`
                )
            );
        } else {
            operator = null;
        }
        requirements.set(requireName, {
            name: requireName,
            operator,
            version: requiredVersion,
        });
    }
    return requirements;
}
