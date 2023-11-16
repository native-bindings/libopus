import { spawn } from "child-process-utilities";
import getPrefixFromSourceDir from "./getPrefixFromSourceDir";
import fs from "fs";
import path from "path";

export interface ILibrary {
    sourceDir: string;
}

/**
 * A class made to compile Makefile or CMake projects and turn them into an interface library
 * for the Node.js bindings CMake project.
 */
export default class Compiler {
    public constructor(
        private readonly librariesDirectory: string,
        private readonly libraries: ILibrary[]
    ) {}
    async compile({ configure }: { configure: boolean }) {
        for (const { sourceDir } of this.libraries) {
            const prefix = getPrefixFromSourceDir({
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

    async #compileMakefile({
        sourceDir,
        configure,
        prefix,
    }: {
        configure: boolean;
        prefix: string;
        sourceDir: string;
    }) {
        await fs.promises.access(
            path.resolve(sourceDir, "configure"),
            fs.constants.R_OK
        );
        if (configure) {
            await spawn("./configure", ["--prefix", prefix], {
                cwd: sourceDir,
            }).wait();
        }
        await spawn("make", [], {
            cwd: sourceDir,
        }).wait();
        await spawn("make", ["install"], {
            cwd: sourceDir,
        }).wait();
    }
}
