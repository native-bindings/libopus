import { spawn } from "child-process-utilities";
import fs from "fs";
import CodeStream from "codestreamjs";
import path from "path";
import semver from "semver";
import fetch from "node-fetch";

export type NodeVersionsResponse = {
    version: string;
    date: string;
    files: string[];
    npm?: string;
    v8: string;
    uv?: string;
    zlib?: string;
    openssl?: string;
    modules?: string;
    lts: string | boolean;
    security: boolean;
}[];

(async () => {
    const cs = new CodeStream();
    const outFile = path.resolve(__dirname, "tested_on.txt");
    await fs.promises.writeFile(outFile, "");
    const availableVersions: NodeVersionsResponse = await (
        await fetch("https://nodejs.org/dist/index.json")
    ).json();
    const nodeVersions: string[] = availableVersions
        .reduce((a, b) => {
            if (semver.lt(b.version, "14.15.0")) {
                return a;
            }
            return [...a, b.version.substring(1)];
        }, new Array<string>())
        .filter((v) => semver.compare(v, "17.0.0") !== 0)
        .sort((a, b) => semver.compare(a, b));
    console.log(
        "Testing for the following Node.js versions:\n%s\n",
        nodeVersions.map((v) => `\t- ${v}`).join("\n")
    );
    for (const test of [
        {
            outName: "Ubuntu",
            image: {
                name: "ubuntu",
                versions: [
                    // "18.04",
                    // "18.10",
                    // "19.04",
                    // "19.10",
                    "20.04",
                    "20.10",
                    "21.04",
                    "21.10",
                    "22.04",
                    "22.10",
                    "23.04",
                    "23.10",
                ],
            },
        },
        {
            outName: "Debian",
            image: {
                name: "debian",
                versions: ["bookworm", "bullseye"],
            },
        },
    ]) {
        for (const version of test.image.versions) {
            await fs.promises.appendFile(
                outFile,
                `## ${test.outName} ${version}\n\n`
            );

            cs.write(`FROM ${test.image.name}:${version}\n\n`);
            cs.write(`ENV VERBOSE=1\n`);
            cs.write(`ENV DEBIAN_FRONTEND=noninteractive\n`);
            cs.write(`RUN apt update\n`);
            cs.write(`RUN apt install -y curl cmake clang libssl-dev\n`);
            cs.write(`WORKDIR /root\n`);
            cs.write(
                "RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.5/install.sh | bash\n"
            );
            // cs.write(`SHELL ["/bin/bash","-l","-c"]\n`);
            // cs.write(`RUN source /root/.bashrc\n`);
            const imageFolder = path.resolve(
                __dirname,
                `${test.image.name}-${version}`
            );
            const dockerFile = path.resolve(imageFolder, "Dockerfile");
            await fs.promises.mkdir(imageFolder, { recursive: true });
            await fs.promises.writeFile(dockerFile, cs.value());

            const imageName = `libopus-test-${test.image.name}:${version}`;

            await spawn("docker", [
                "build",
                "-t",
                imageName,
                imageFolder,
            ]).wait();

            for (const version of nodeVersions) {
                const testNodeScriptFileName = path.resolve(
                    imageFolder,
                    `test-node-${version}.sh`
                );
                cs.write(`#!/bin/bash\n`);
                cs.write(`nvm install ${version}\n`);
                cs.write(`nvm use ${version}\n`);
                cs.write(`npm init --yes\n`);
                cs.write(`npm i libopus\n`);
                cs.write(`node -e 'console.log(require("libopus"))'\n`);
                await fs.promises.writeFile(testNodeScriptFileName, cs.value());
                await spawn("chmod", ["+x", testNodeScriptFileName]).wait();
                await spawn("docker", [
                    "run",
                    "--rm",
                    "-v",
                    `${testNodeScriptFileName}:/root/test.sh`,
                    "-v",
                    `${outFile}:/root/${path.basename(outFile)}`,
                    "-it",
                    imageName,
                    "bash",
                    "-i",
                    "test.sh",
                ]).wait();
                await fs.promises.appendFile(outFile, `- Node.js ${version}\n`);
            }
        }
    }
})().catch((reason) => {
    console.error(reason);
    process.exitCode = 1;
});
