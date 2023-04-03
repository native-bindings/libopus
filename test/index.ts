import opus from "..";
import child_process from "child_process";
import path from "path";
import assert from "assert";

async function testOpusCodec() {
    const sampleRate = 48000;
    const channels = 1;
    const enc = new opus.Encoder(
        sampleRate,
        1,
        opus.constants.OPUS_APPLICATION_RESTRICTED_LOWDELAY
    );
    /**
     * frame size in samples
     */
    const frameSize = 2880;
    const bufferSize = Float32Array.BYTES_PER_ELEMENT * frameSize;
    const dec = new opus.Decoder(sampleRate, 1);
    const pcm = child_process.spawn("arecord", [
        "-f",
        "FLOAT_LE",
        "-c",
        channels.toString(),
        `--buffer-size=${bufferSize}`,
        "-r",
        sampleRate.toString(),
        "-d",
        "4",
    ]);
    const encoded = new Uint8Array(10000);
    const pcmOut = new Float32Array(
        frameSize * channels * Float32Array.BYTES_PER_ELEMENT
    );
    const aplay = child_process.spawn("aplay", [
        "-f",
        "FLOAT_LE",
        "-r",
        sampleRate.toString(),
        "-c",
        channels.toString(),
        "-i",
    ]);
    pcm.stdout.on("data", (chunk) => {
        assert.strict.ok(Buffer.isBuffer(chunk));
        const samples = chunk.byteLength / Float32Array.BYTES_PER_ELEMENT;
        const buf = new Float32Array(samples);
        buf.set(new Float32Array(chunk.buffer, chunk.byteOffset, samples));

        const encodedSampleCount = enc.encodeFloat(
            buf,
            frameSize,
            encoded,
            1000
        );

        console.log("encoded samples: %d", encodedSampleCount);

        const decodedSamples = dec.decodeFloat(
            encoded,
            encodedSampleCount,
            pcmOut,
            frameSize,
            0
        );

        console.log("decoded samples: %d", decodedSamples);

        aplay.stdin.write(
            new Uint8Array(pcmOut.slice(0, decodedSamples).buffer)
        );
    });
    return new Promise<void>((resolve, reject) => {
        pcm.on("exit", (code) => {
            if (code !== 0) {
                reject(new Error(`process exited with invalid code: ${code}`));
                return;
            }
            /**
             * end stdin stream
             */
            aplay.stdin.end();
            /**
             * kill play sound process
             */
            if (!aplay.kill(0)) {
                reject(new Error("failed to kill play sound process"));
                return;
            }
            resolve();
        });
    });
}

async function createFile() {
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
    pcm.stdout.on("end", () => {
        enc.drain();
    });
    return new Promise<void>((resolve, reject) => {
        pcm.on("exit", (code) => {
            if (code !== 0) {
                reject(new Error(`process exited with wrong code: ${code}`));
            } else {
                resolve();
            }
        });
    });
}

(async () => {
    await testOpusCodec();
    await createFile();
})().catch((reason) => {
    process.exitCode = 1;
    console.error(reason);
});
