"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const child_process_utilities_1 = require("child-process-utilities");
const getPrefixFromSourceDir_1 = __importDefault(require("./getPrefixFromSourceDir"));
const fs_1 = __importDefault(require("fs"));
const path_1 = __importDefault(require("path"));
/**
 * A class made to compile Makefile or CMake projects and turn them into an interface library
 * for the Node.js bindings CMake project.
 */
class Compiler {
    librariesDirectory;
    libraries;
    constructor(librariesDirectory, libraries) {
        this.librariesDirectory = librariesDirectory;
        this.libraries = libraries;
    }
    async compile({ configure }) {
        for (const { sourceDir } of this.libraries) {
            const prefix = (0, getPrefixFromSourceDir_1.default)({
                libsDir: this.librariesDirectory,
                sourceDir,
            });
            await this.#compileMakefile({
                configure,
                sourceDir,
                prefix,
            });
        }
    }
    async #compileMakefile({ sourceDir, configure, prefix, }) {
        await fs_1.default.promises.access(path_1.default.resolve(sourceDir, "configure"), fs_1.default.constants.R_OK);
        if (configure) {
            await (0, child_process_utilities_1.spawn)("./configure", ["--prefix", prefix], {
                cwd: sourceDir,
            }).wait();
        }
        await (0, child_process_utilities_1.spawn)("make", [], {
            cwd: sourceDir,
        }).wait();
        await (0, child_process_utilities_1.spawn)("make", ["install"], {
            cwd: sourceDir,
        }).wait();
    }
}
exports.default = Compiler;
//# sourceMappingURL=Compiler.js.map