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
import { IPkgConfigLibrary } from "./getLinkLibrariesFromRequiresLine";
import parseRequiresLine from "./parseRequiresLine";

async function parsePkgConfigFile(pkgConfigFile: string) {
    try {
        return new PkgConfigFileParser({
            contents: await fs.promises.readFile(pkgConfigFile, "utf8"),
            file: pkgConfigFile,
        }).parse();
    } catch (reason) {
        console.error("Failure while parsing file: %s", pkgConfigFile);
        throw reason;
    }
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

function getPkgConfigPath({
    sourceDir,
    libsDir,
}: {
    sourceDir: string;
    libsDir: string;
}) {
    const installDir = getPrefixFromSourceDir({
        sourceDir,
        libsDir,
    });
    return path.resolve(installDir, "lib/pkgconfig");
}

export default class InterfaceLibrariesGenerator {
    readonly #pcFiles = new Map<string, Map<string, string>>();
    readonly #libraryPcFiles = new Map<ILibrary, string[]>();
    public constructor(private readonly librariesDirectory: string) {}
    public async generateInterfaceLibraries(inputLibraries: ILibrary[]) {
        const cs = new CodeStream();
        for (const lib of inputLibraries) {
            const folder = getPkgConfigPath({
                sourceDir: lib.sourceDir,
                libsDir: this.librariesDirectory,
            });
            const files = await glob(path.resolve(folder, "*.pc"));
            for (const pcFile of files) {
                const key = path.basename(pcFile).replace(/\.pc$/, "");
                let values = this.#pcFiles.get(key);
                if (!values) {
                    values = new Map<string, string>();
                    this.#pcFiles.set(key, values);
                }
                const parsed = await parsePkgConfigFile(pcFile);
                for (const [key, value] of parsed) {
                    values.set(key, value);
                }
            }
            this.#libraryPcFiles.set(lib, files);
        }
        for (const lib of inputLibraries) {
            const packageConfigFiles = this.#libraryPcFiles.get(lib);
            assert.strict.ok(
                typeof packageConfigFiles !== "undefined" &&
                    packageConfigFiles.length > 0,
                `missing package config files for ${lib.sourceDir}`
            );
            const libraries = new Map<string, IPkgConfigLibrary>();
            for (const packageConfigFile of packageConfigFiles) {
                const values = await parsePkgConfigFile(packageConfigFile);
                const libraryName = values.get("Name");
                assert.strict.ok(
                    typeof libraryName === "string",
                    "missing name"
                );
                libraries.set(libraryName.trim(), {
                    file: packageConfigFile,
                    values: new Map<string, string>(
                        Array.from(values).map(([key, value]) => [
                            key.trim(),
                            value.trim(),
                        ])
                    ),
                });
            }

            for (const [libraryName, { values, file }] of libraries) {
                const libs = values.get("Libs");
                const cflags = values.get("Cflags");
                const linkLibraries = new Array<string>();
                // const privateLinkLibraries = new Array<string>();

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

                const includeDirectories = joinAsString(
                    parsed.includeDirectories
                );

                const compileOptions = joinAsString(
                    parsed.remaining.split(" ")
                );

                cs.write(`add_library(${libraryName} INTERFACE)\n`);
                if (includeDirectories) {
                    cs.write(
                        `target_include_directories(${libraryName} INTERFACE ${includeDirectories})\n`
                    );
                }
                if (compileOptions) {
                    cs.write(
                        `target_compile_options(${libraryName} INTERFACE ${compileOptions})\n`
                    );
                }
                for (const item of [
                    {
                        requires: values.get("Requires") ?? null,
                        list: linkLibraries,
                    },
                    // {
                    //     requires: values.get("Requires.private"),
                    //     list: privateLinkLibraries,
                    // },
                ]) {
                    if (!item.requires) {
                        continue;
                    }
                    const requirements = parseRequiresLine({
                        value: item.requires,
                        file,
                    });
                    for (const pcFileName of requirements.keys()) {
                        const pcFile = this.#pcFiles.get(pcFileName);
                        assert.strict.ok(
                            typeof pcFile !== "undefined",
                            `missing pc file for ${pcFileName}`
                        );
                        const linkLibraryName = pcFile.get("Name");
                        assert.strict.ok(
                            typeof linkLibraryName !== "undefined",
                            `missing name for ${pcFileName}`
                        );
                        item.list.push(linkLibraryName);
                    }
                    // item.list.push(
                    //     ...getLinkLibrariesFromRequiresLine({
                    //         requires: item.requires,
                    //         file,
                    //         libraryName,
                    //         libraries,
                    //     })
                    // );
                }
                const findLibraryVarName =
                    getFindLibraryVariableName(libraryName);
                const linkLibraryName = parsed.libraries[0];
                assert.strict.ok(
                    typeof linkLibraryName === "string",
                    `missing link library name for ${libraryName}`
                );
                cs.write(
                    `find_library(${findLibraryVarName} ${linkLibraryName} HINTS ${joinAsString(
                        parsed.searchDirectories
                    )} REQUIRED)\n`
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
