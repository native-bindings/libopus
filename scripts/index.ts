import path from "path";
import fs from "fs";
import {
    Compiler,
    InterfaceLibrariesGenerator,
    PreprocessorParser,
    PreprocessorTokenizer,
} from "../core";
import { getArgument } from "cli-argument-helper";
import { spawn } from "child-process-utilities";
import { glob } from "glob";
import Exception from "../core/Exception";
import LibraryConstantsGenerator from "./LibraryConstantsGenerator";

const libsDir = path.resolve(__dirname, "../third-party");
const prefix = path.resolve(__dirname, "../libs");

function formatMilliseconds(milliseconds: number) {
    const seconds = milliseconds / 1000;
    const minutes = seconds / 60;
    const hours = minutes / 60;
    const list = new Array<string>();

    if (hours >= 1) {
        list.push(`${hours.toFixed(2)}h`);
    }

    if (minutes >= 1) {
        list.push(`${minutes.toFixed(2)}m`);
    }

    if (seconds >= 1) {
        list.push(`${seconds.toFixed(2)}s`);
    }

    return `${list.join("")}${milliseconds.toFixed(2)}ms`;
}

import perf_hooks from "perf_hooks";

class Timer {
    #start: number;

    constructor() {
        this.#start = perf_hooks.performance.now();
    }

    public mark() {
        this.#start = perf_hooks.performance.now();
    }

    public elapsed() {
        return perf_hooks.performance.now() - this.#start;
    }

    public toString() {
        return formatMilliseconds(this.elapsed());
    }
}

const libDirectories = [
    { sourceDir: path.resolve(libsDir, "opus-v1.4") },
    { sourceDir: path.resolve(libsDir, "ogg-v1.3.5") },
    { sourceDir: path.resolve(libsDir, "speexdsp-SpeexDSP-1.2.1") },
    { sourceDir: path.resolve(libsDir, "opusfile-v0.12") },
    { sourceDir: path.resolve(libsDir, "libopusenc-v0.2.1") },
];

async function generateConstants() {
    const constantsGenerator = new LibraryConstantsGenerator();

    interface IFileParsingStats {
        fileReadTime: string | null;
        tokenizationTime: string | null;
        parsingTime: string | null;
        constantsProcessingTime: string | null;
    }

    const timer = new Timer();
    const stats = new Map<string, IFileParsingStats>();
    const finalStats: {
        stats: Map<string, IFileParsingStats>;
        constantsCodeGenerationTime: string | null;
    } = {
        stats,
        constantsCodeGenerationTime: null,
    };

    for (const libDirectory of libDirectories) {
        const headerFiles = await glob(
            path.resolve(libDirectory.sourceDir, "**/*.h"),
        );
        for (const headerFile of headerFiles) {
            const fileStats: IFileParsingStats = {
                fileReadTime: null,
                tokenizationTime: null,
                parsingTime: null,
                constantsProcessingTime: null,
            };

            timer.mark();
            const contents = await fs.promises.readFile(headerFile);
            fileStats.fileReadTime = timer.toString();

            timer.mark();
            const tokens = new PreprocessorTokenizer({
                contents,
                file: headerFile,
            }).tokenize();
            fileStats.tokenizationTime = timer.toString();

            timer.mark();
            const nodes = new PreprocessorParser({
                contents,
                tokens,
                file: headerFile,
            }).parse();
            fileStats.parsingTime = timer.toString();

            timer.mark();
            constantsGenerator.process(nodes);
            fileStats.constantsProcessingTime = timer.toString();

            stats.set(headerFile, fileStats);
        }
    }

    timer.mark();
    await constantsGenerator.generate();
    finalStats.constantsCodeGenerationTime = timer.toString();

    return finalStats;
}

async function run() {
    const args = process.argv.slice(2);
    const configure = getArgument(args, "--configure") !== null;

    if (getArgument(args, "--generate-constants") !== null) {
        await generateConstants();
        return;
    }

    if (getArgument(args, "--skip-third-party") === null) {
        const compiler = new Compiler(prefix, libDirectories);
        await compiler.compile({
            configure,
        });
    }

    /**
     * generate interface libraries
     */
    const generator = new InterfaceLibrariesGenerator(prefix);
    await generator.generateInterfaceLibraries(libDirectories);

    const buildDir = path.resolve(__dirname, "../build");

    for (const isDebug of [true, false]) {
        const args = [
            "cmake-js",
            "compile",
            "--out",
            path.resolve(buildDir, isDebug ? "debug" : "release"),
        ];
        if (isDebug) {
            args.splice(2, 0, "--debug");
        }
        await spawn("npx", args, {
            cwd: path.dirname(__dirname),
        }).wait();
    }
}

run().catch((reason) => {
    if (reason instanceof Exception) {
        console.error(reason.what);
    } else {
        console.error(reason);
    }
});
