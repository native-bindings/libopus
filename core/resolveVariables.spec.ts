import test from "ava";
import mapVariablePositions from "./mapVariablePositions";
import resolveVariables from "./resolveVariables";

test("resolveVariables: it should resolve variables of pkg config files", (t) => {
    t.deepEqual(
        mapVariablePositions("hello ${a}, ${b} and ${c}!"),
        new Map([
            ["a", { start: 6, end: 9 }],
            ["b", { start: 12, end: 15 }],
            ["c", { start: 21, end: 24 }]
        ])
    );

    t.deepEqual(
        resolveVariables(
            "final",
            new Map([
                ["final", "hello ${a}, ${b} and ${c}!"],
                ["a", "${prefix} ${name}"],
                ["name", "Queiroz"],
                ["prefix", "Mr."],
                ["b", "${prefix} ${name}"],
                ["c", "${prefix} ${name}"]
            ])
        ),
        "hello Mr. Queiroz, Mr. Queiroz and Mr. Queiroz!"
    );
});
