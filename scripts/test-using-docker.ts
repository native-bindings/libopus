import { spawn } from "child-process-utilities";
import fs from "fs";
import CodeStream from "codestreamjs";
import path from "path";
import semver from "semver";
import fetch from "node-fetch";
import packageJson from "../package.json";
import assert from "assert";

interface IDockerImage {
    outName: string;
    image: {
        name: string;
        versions: string[];
    };
}

const images: IDockerImage[] = [
    {
        outName: "Ubuntu",
        image: {
            name: "ubuntu",
            versions: [
                "20.04",
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
];

async function testNodeVersion({
    imageFolder,
    packedFile,
    cacheDir,
    imageName,
    outFile,
    version,
}: {
    outFile: string;
    cacheDir: string;
    imageName: string;
    imageFolder: string;
    version: string;
    packedFile: string;
}) {
    const cs = new CodeStream();
    const testNodeScriptFileName = path.resolve(
        imageFolder,
        `test-node-${version}.sh`
    );
    cs.write(`#!/bin/bash\n`);
    cs.write(`nvm install ${version}\n`);
    cs.write(`nvm use ${version}\n`);
    cs.write(`npm init --yes\n`);
    cs.write(`npm i /opt/libopus.tgz\n`);
    cs.write(`node -e 'console.log(require("libopus"))'\n`);
    await fs.promises.writeFile(testNodeScriptFileName, cs.value());
    await spawn("chmod", ["+x", testNodeScriptFileName]).wait();
    await spawn("docker", [
        "run",
        "--rm",
        "-v",
        `${packedFile}:/opt/libopus.tgz`,
        "-v",
        `${path.resolve(
            cacheDir,
            "nvm/versions/node"
        )}:/root/.nvm/versions/node`,
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

async function testImage({
    test,
    outFile,
    cacheDir,
    nodeVersions,
    packedFile,
}: {
    nodeVersions: string[];
    packedFile: string;
    cacheDir: string;
    outFile: string;
    test: IDockerImage;
}) {
    const cs = new CodeStream();
    for (const version of test.image.versions) {
        await fs.promises.appendFile(
            outFile,
            `## ${test.outName} ${version}\n\n`
        );

        cs.write(`FROM ${test.image.name}:${version}\n\n`);
        cs.write(`ENV VERBOSE=1\n`);
        cs.write(`ENV NODE_ENV=production\n`);
        cs.write(`ENV DEBIAN_FRONTEND=noninteractive\n`);
        cs.write(`RUN apt update\n`);
        cs.write(`RUN apt install -y git curl bash cmake clang\n`);
        cs.write(`WORKDIR /root\n`);
        cs.write(
            "RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.5/install.sh | bash\n"
        );
        const imageFolder = path.resolve(
            cacheDir,
            `images/${test.image.name}-${version}`
        );
        const dockerFile = path.resolve(imageFolder, "Dockerfile");
        await fs.promises.mkdir(imageFolder, { recursive: true });
        await fs.promises.writeFile(dockerFile, cs.value());

        const imageName = `libopus-test-${test.image.name}:${version}`;

        await spawn("docker", ["build", "-t", imageName, imageFolder]).wait();

        // const pending = new Array<Promise<void>>();

        for (const version of nodeVersions) {
            await testNodeVersion({
                imageFolder,
                packedFile,
                cacheDir,
                imageName,
                outFile,
                version,
            });
            // pending.push(
            //     testNodeVersion({
            //         imageFolder,
            //         packedFile,
            //         cacheDir,
            //         imageName,
            //         outFile,
            //         version,
            //     })
            // );
        }

        // await Promise.all(pending);
    }
}

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
    const cacheDir = path.resolve(__dirname, ".cache");
    const outFile = path.resolve(__dirname, "tested_on.txt");
    await fs.promises.writeFile(outFile, "");
    const availableVersions: NodeVersionsResponse = await (
        await fetch("https://nodejs.org/dist/index.json")
    ).json();
    const nodeVersions: string[] = availableVersions
        .reduce((a, b) => {
            if (semver.lt(b.version, "14.15.1")) {
                return a;
            }
            const existing = a.find(
                (v) => semver.major(v) === semver.major(b.version)
            );
            if (existing) {
                /**
                 * if the existing version is greater than the current version, we ignore it. thus, we only keep the latest version of each major version.
                 */
                if (semver.lt(b.version, existing)) {
                    return a;
                }
                /**
                 * if the existing version is less than the current version, we remove it from the array.
                 */
                a = a.filter((v) => v !== existing);
            }
            return [...a, b.version.substring(1)];
        }, new Array<string>())
        .filter((v) => semver.compare(v, "17.0.0") !== 0)
        .sort((a, b) => semver.compare(a, b));
    const packsDir = path.resolve(cacheDir, "packs");
    try {
        await fs.promises.access(
            packsDir,
            fs.constants.R_OK | fs.constants.W_OK
        );
        assert.strict.ok((await fs.promises.stat(packsDir)).isDirectory());
    } catch (reason) {
        await fs.promises.rm(packsDir, { force: true, recursive: true });
        await fs.promises.mkdir(packsDir, { recursive: true });
    }
    await spawn("npm", ["pack", "--pack-destination", packsDir], {
        cwd: path.dirname(__dirname),
    }).wait();
    const packedFile = path.resolve(
        packsDir,
        `${packageJson.name}-${packageJson.version}.tgz`
    );
    console.log(
        "Testing for the following Node.js versions:\n%s\n",
        nodeVersions.map((v) => `\t- ${v}`).join("\n")
    );
    for (const test of images) {
        await testImage({
            packedFile,
            outFile,
            test,
            cacheDir,
            nodeVersions,
        });
    }
})().catch((reason) => {
    console.error(reason);
    process.exitCode = 1;
});
