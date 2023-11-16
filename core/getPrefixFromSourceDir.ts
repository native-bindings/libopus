import assert from "assert";
import path from "path";

export default function getPrefixFromSourceDir({
    sourceDir,
    libsDir,
}: {
    libsDir: string;
    sourceDir: string;
}) {
    assert.strict.ok(path.isAbsolute(sourceDir));
    return path.resolve(libsDir, path.basename(sourceDir));
}
