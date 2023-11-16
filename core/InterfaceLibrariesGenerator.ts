import CodeStream from "textstreamjs";
import fs from "fs";
import PkgConfigFileParser from "./PkgConfigFileParser";
import getPrefixFromSourceDir from "./getPrefixFromSourceDir";
import path from "path";
import assert from "assert";
import parseArgumentsLine, {
    mergeParsedArgumentsLine,
} from "./parseArgumentsLine";
import { ILibrary } from "./Compiler";
import { glob } from "glob";

async function parsePkgConfigFile(pkgConfigFile: string) {
    return new PkgConfigFileParser(
        await fs.promises.readFile(pkgConfigFile, "utf8")
    ).parse();
}

function getFindLibraryVariableName(libraryName: string) {
    return `${libraryName.replace(/\+/g, "_plus").toUpperCase()}_LIB`;
}

function joinAsString(value: string[]) {
    return value
        .map((v) => v.trim())
        .filter((v) => v.length > 0)
        .map((v) => `"${v}"`)
        .join(" ");
}

export default class InterfaceLibrariesGenerator {
    public constructor(private readonly librariesDirectory: string) {}
    public async generateInterfaceLibraries(inputLibraries: ILibrary[]) {
        const cs = new CodeStream();
        for (const { sourceDir } of inputLibraries) {
            const installDir = getPrefixFromSourceDir({
                sourceDir,
                libsDir: this.librariesDirectory,
            });
            const pkgConfigPath = path.resolve(installDir, "lib/pkgconfig");
            const packageConfigFiles = await glob(
                path.resolve(pkgConfigPath, "*.pc")
            );
            const libraries = new Map<string, ReadonlyMap<string, string>>();
            for (const packageConfigFile of packageConfigFiles) {
                const values = await parsePkgConfigFile(packageConfigFile);
                const libraryName = values.get("Name");
                assert.strict.ok(typeof libraryName === "string");
                libraries.set(
                    libraryName,
                    new Map<string, string>(
                        [...values].map(([key, value]) => [
                            key.trim(),
                            value.trim(),
                        ])
                    )
                );
            }

            for (const [libraryName, values] of libraries) {
                const libs = values.get("Libs");
                const linkLibraryName = values.get("libname");
                const requires = values.get("Requires");
                const cflags = values.get("Cflags");
                assert.strict.ok(
                    typeof libs === "string" && typeof libraryName === "string"
                );

                let parsed = parseArgumentsLine(libs);

                if (cflags) {
                    parsed = mergeParsedArgumentsLine(
                        parsed,
                        parseArgumentsLine(cflags)
                    );
                }

                cs.write(`add_library(${libraryName} INTERFACE)\n`);
                cs.write(
                    `target_include_directories(${libraryName} INTERFACE ${joinAsString(
                        parsed.includeDirectories
                    )})\n`
                );
                cs.write(
                    `target_compile_options(${libraryName} INTERFACE ${joinAsString(
                        parsed.remaining.split(" ")
                    )})\n`
                );
                const linkLibraries = new Array<string>();
                if (requires) {
                    const dependency = Array.from(libraries.values()).find(
                        (l) => l.get("libname") === requires
                    );
                    assert.strict.ok(
                        dependency,
                        `missing dependency: ${requires}`
                    );
                    const cmakeLibraryName = dependency.get("Name");
                    assert.strict.ok(
                        cmakeLibraryName,
                        `missing cmake library name for ${requires}`
                    );
                    linkLibraries.push(cmakeLibraryName);
                }
                const findLibraryVarName =
                    getFindLibraryVariableName(libraryName);
                cs.write(
                    `find_library(${findLibraryVarName} ${linkLibraryName} HINTS ${joinAsString(
                        parsed.searchDirectories
                    )})\n`
                );
                linkLibraries.push(`\${${findLibraryVarName}}`);
                cs.write(
                    `target_link_libraries(${libraryName} INTERFACE ${linkLibraries.join(
                        " "
                    )})\n`
                );
                cs.write("\n");
            }
        }
        await fs.promises.writeFile(
            path.resolve(this.librariesDirectory, "CMakeLists.txt"),
            cs.value()
        );
    }
}
