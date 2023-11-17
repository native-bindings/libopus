import assert from "assert";
import parseRequiresLine from "./parseRequiresLine";

export interface IPkgConfigLibrary {
    values: Map<string, string>;
    file: string;
}

export default function getLinkLibrariesFromRequiresLine({
    libraries,
    requires,
    file,
    libraryName,
}: {
    requires: string;
    file: string;
    libraryName: string;
    libraries: Map<string, IPkgConfigLibrary>;
}) {
    const requirements = parseRequiresLine({
        value: requires,
        file,
    });
    const linkLibraries = new Array<string>();
    for (const req of requirements.values()) {
        const dependency = Array.from(libraries.values()).find(
            (l) => l.values.get("Name") === req.name
        );
        assert.strict.ok(
            dependency,
            `missing ${libraryName} dependency: ${req.name}`
        );
        const cmakeLibraryName = dependency.values.get("Name");
        assert.strict.ok(
            cmakeLibraryName,
            `missing cmake library name for ${req.name}`
        );
        linkLibraries.push(cmakeLibraryName);
    }
    return linkLibraries;
}
