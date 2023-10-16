# libopus

## Installation

```
yarn add libopus
```

## Description

Entirely synchronous API to create .ogg files encoded using libopus library. It supports several sample rates (16000,48000 and more.).

## Usage of libopus

Below it's an example on how to use the opus codec by itself, without interference of the libopusenc. AFAIK, the encoded data cannot be directly placed in a .ogg file for playing. If you need that, see the next example.

```ts
import opus from "libopus";

export function createTestCodec() {
    const frameSize = 2880;
    const sampleRate = 48000;
    const channels = 1;

    const enc = new opus.Encoder(
        sampleRate,
        channels,
        opus.constants.OPUS_APPLICATION_RESTRICTED_LOWDELAY
    );
    const dec = new opus.Decoder(sampleRate, channels);

    const pcmOut = new Float32Array(
        frameSize * channels * Float32Array.BYTES_PER_ELEMENT
    );

    const encoded = new Uint8Array(10000);
    const maxDataBytes = 1000; // it can be increased up to whatever `encoded` size is

    const encodeFloat = (buf: Float32Array) => {
        const encodedSampleCount = enc.encodeFloat(
            buf,
            frameSize,
            encoded,
            maxDataBytes
        );
        console.log("encoded samples: %d", encodedSampleCount);
        return encodedSampleCount;
    };

    const decodeFloat = (buf: Uint8Array, samples: number) => {
        const decodedSamples = dec.decodeFloat(
            buf,
            samples,
            pcmOut,
            frameSize,
            0
        );
        return new Uint8Array(pcmOut.slice(0, decodedSamples).buffer);
    };

    const encodeAndDecode = (buf: Float32Array) => {
        const encodedSampleCount = encodeFloat(buf);
        return decodeFloat(encoded, encodedSampleCount);
    };

    return {
        decode,
        encode,
        encodeAndDecode,
    };
}
```

## Usage of libopusenc

This package comes with libopusenc embedded in it, so you can create .ogg/.opus files directly with it with any sample rate. It will use speexdsp in case a sample rate that is not supported by libopus is used when creating the encoder. See the example below:

```ts
import opus from "libopus";

const comments = new opus.opusenc.Comments();
const enc = new opus.opusenc.Encoder();
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

## Usage of opusfile

```ts
import { OpusFile } from "libopus";

const of = new OpusFile();
of.openFile(path.resolve(__dirname, "sample-3.opus"));
const pcm = new Float32Array(2880);
assert.strict.equal(of.pcmTell(), 0);
assert.strict.deepEqual(of.readFloat(pcm), {
    sampleCount: 648,
    linkIndex: 0,
});
assert.strict.deepEqual(of.pcmTell(), 648);
assert.strict.deepEqual(of.readFloat(pcm), {
    sampleCount: 960,
    linkIndex: 0,
});
assert.strict.equal(of.pcmTell(), 1608);
assert.strict.equal(of.pcmSeek(0), undefined);
assert.strict.equal(of.pcmTell(), 0);
assert.strict.deepEqual(of.readFloat(pcm), {
    sampleCount: 648,
    linkIndex: 0,
});
assert.strict.equal(of.channelCount(0), 2);
assert.strict.equal(of.channelCount(1), 2);
assert.strict.equal(of.linkCount(), 1);
assert.strict.equal(of.rawTotal(0), 705632);
```
