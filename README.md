# node-opusenc

## Description

Entirely synchronous API to create .ogg files encoded using libopus library. It supports several sample rates (16000,48000 and more.).

## Usage

```ts
import { Comments, Encoder } from "node-opusenc";

const comments = new Comments();
const enc = new Encoder();
enc.createFile(comments, path.resolve(__dirname, "test1.ogg"), 48000, 1, 0);
const pcm = child_process.spawn("arecord", [
    "-f",
    "FLOAT_LE",
    "-c",
    "1",
    "-r",
    "48000",
    "-d",
    "4",
]);
pcm.stdout.on("data", (chunk) => {
    assert.strict.ok(Buffer.isBuffer(chunk));
    const samples = chunk.byteLength / Float32Array.BYTES_PER_ELEMENT;
    const buf = new Float32Array(samples);
    buf.set(new Float32Array(chunk.buffer, chunk.byteOffset, samples));

    enc.writeFloat(buf, samples);
});
return new Promise<void>((resolve) => {
    pcm.stdout.on("exit", (code) => {
        assert.strict.ok(code === 0);
        enc.drain();
        resolve();
    });
});
```
