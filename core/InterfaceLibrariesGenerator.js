"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const textstreamjs_1 = __importDefault(require("textstreamjs"));
const fs_1 = __importDefault(require("fs"));
const PkgConfigFileParser_1 = __importDefault(require("./PkgConfigFileParser"));
const getPrefixFromSourceDir_1 = __importDefault(require("./getPrefixFromSourceDir"));
const path_1 = __importDefault(require("path"));
const assert_1 = __importDefault(require("assert"));
const parseArgumentsLine_1 = __importStar(require("./parseArgumentsLine"));
const glob_1 = require("glob");
async function parsePkgConfigFile(pkgConfigFile) {
    return new PkgConfigFileParser_1.default(await fs_1.default.promises.readFile(pkgConfigFile, "utf8")).parse();
}
function getFindLibraryVariableName(libraryName) {
    return `${libraryName.replace(/\+/g, "_plus").toUpperCase()}_LIB`;
}
function joinAsString(value) {
    return value
        .map((v) => v.trim())
        .filter((v) => v.length > 0)
        .map((v) => `"${v}"`)
        .join(" ");
}
class InterfaceLibrariesGenerator {
    librariesDirectory;
    constructor(librariesDirectory) {
        this.librariesDirectory = librariesDirectory;
    }
    async generateInterfaceLibraries(inputLibraries) {
        const cs = new textstreamjs_1.default();
        for (const { sourceDir } of inputLibraries) {
            const installDir = (0, getPrefixFromSourceDir_1.default)({
                sourceDir,
                libsDir: this.librariesDirectory,
            });
            const pkgConfigPath = path_1.default.resolve(installDir, "lib/pkgconfig");
            const packageConfigFiles = await (0, glob_1.glob)(path_1.default.resolve(pkgConfigPath, "*.pc"));
            const libraries = new Map();
            for (const packageConfigFile of packageConfigFiles) {
                const values = await parsePkgConfigFile(packageConfigFile);
                const libraryName = values.get("Name");
                assert_1.default.strict.ok(typeof libraryName === "string");
                libraries.set(libraryName, new Map([...values].map(([key, value]) => [
                    key.trim(),
                    value.trim(),
                ])));
            }
            for (const [libraryName, values] of libraries) {
                const libs = values.get("Libs");
                const linkLibraryName = values.get("libname");
                const requires = values.get("Requires");
                const cflags = values.get("Cflags");
                assert_1.default.strict.ok(typeof libs === "string" && typeof libraryName === "string");
                let parsed = (0, parseArgumentsLine_1.default)(libs);
                if (cflags) {
                    parsed = (0, parseArgumentsLine_1.mergeParsedArgumentsLine)(parsed, (0, parseArgumentsLine_1.default)(cflags));
                }
                cs.write(`add_library(${libraryName} INTERFACE)\n`);
                cs.write(`target_include_directories(${libraryName} INTERFACE ${joinAsString(parsed.includeDirectories)})\n`);
                cs.write(`target_compile_options(${libraryName} INTERFACE ${joinAsString(parsed.remaining.split(" "))})\n`);
                const linkLibraries = new Array();
                if (requires) {
                    const dependency = Array.from(libraries.values()).find((l) => l.get("libname") === requires);
                    assert_1.default.strict.ok(dependency, `missing dependency: ${requires}`);
                    const cmakeLibraryName = dependency.get("Name");
                    assert_1.default.strict.ok(cmakeLibraryName, `missing cmake library name for ${requires}`);
                    linkLibraries.push(cmakeLibraryName);
                }
                const findLibraryVarName = getFindLibraryVariableName(libraryName);
                cs.write(`find_library(${findLibraryVarName} ${linkLibraryName} HINTS ${joinAsString(parsed.searchDirectories)})\n`);
                linkLibraries.push(`\${${findLibraryVarName}}`);
                cs.write(`target_link_libraries(${libraryName} INTERFACE ${linkLibraries.join(" ")})\n`);
                cs.write("\n");
            }
        }
        await fs_1.default.promises.writeFile(path_1.default.resolve(this.librariesDirectory, "CMakeLists.txt"), cs.value());
    }
}
exports.default = InterfaceLibrariesGenerator;
//# sourceMappingURL=InterfaceLibrariesGenerator.js.map