import opus from "..";
import path from "path";
import { IOptions, aplay, arecord } from "./arecord";
import { Observable, finalize, lastValueFrom, mergeMap } from "rxjs";
import RingBuffer, { ITypedArray } from "./RingBuffer";
// import inspector from "inspector";
// import { ChildProcessWithoutNullStreams } from "child_process";
import assert from "assert";
import Exception from "./Exception";
import { Writable } from "stream";
import crypto from "crypto";
import inspector from "inspector";
import chalk from "chalk";
import { Converter } from "./helpers";

if (process.argv.includes("--inspect")) {
    inspector.open(undefined, undefined, true);
}

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
    // const bufferSize = frameSize * Float32Array.BYTES_PER_ELEMENT;
    const dec = new opus.Decoder(sampleRate, 1);
    const options: IOptions = {
        format: "FLOAT_LE",
        channels: 1,
        sampleRate,
    };
    const pcm = arecord({
        ...options,
        duration: 4,
    });
    const encoded = new Uint8Array(10000);
    const pcmOut = new Float32Array(frameSize * channels);
    const player = aplay({
        format: "FLOAT_LE",
        channels: 1,
        sampleRate,
    });
    pcm.subscribe((chunk) => {
        const samples = chunk.byteLength / Float32Array.BYTES_PER_ELEMENT;
        const buf = new Float32Array(samples);
        buf.set(new Float32Array(chunk.buffer, chunk.byteOffset, samples));

        const encodedSampleCount = enc.encodeFloat(
            buf,
            frameSize,
            encoded,
            1000
        );

        const decodedSamples = dec.decodeFloat(
            encoded,
            encodedSampleCount,
            pcmOut,
            frameSize,
            0
        );

        player.stdin.write(
            new Uint8Array(pcmOut.slice(0, decodedSamples).buffer)
        );
    });
    return lastValueFrom(pcm).then(() => {
        player.stdin.end();
    });
}

async function createFile() {
    const comments = new opus.opusenc.Comments();
    const enc = new opus.opusenc.Encoder();
    enc.createFile(comments, path.resolve(__dirname, "test1.ogg"), 48000, 1, 0);
    const pcm = arecord({
        sampleRate: 48000,
        duration: 4,
        channels: 1,
        format: "FLOAT_LE",
    });
    pcm.subscribe((chunk) => {
        const samples = chunk.byteLength / Float32Array.BYTES_PER_ELEMENT;
        const buf = new Float32Array(samples);
        buf.set(new Float32Array(chunk.buffer, chunk.byteOffset, samples));

        enc.writeFloat(buf, samples);
    });
    return lastValueFrom(pcm);
}

async function testDecoder({
    frameSize,
    sampleRate,
}: {
    sampleRate: number;
    frameSize: number;
}) {
    const channelCount = 1;
    const encoder = new opus.Encoder(
        sampleRate,
        channelCount,
        opus.constants.OPUS_APPLICATION_AUDIO
    );
    const encoded = new Uint8Array(1024 * 1024 * 2);
    const converter = new Converter(sampleRate);
    const decoder = new opus.Decoder(sampleRate, channelCount);
    const sampleCount =
        converter.frameSizeToByteLength(frameSize) /
        Int16Array.BYTES_PER_ELEMENT;
    const outPcm = new Int16Array(sampleCount * channelCount);
    const aplayFrameSize = 300;
    const options: IOptions = {
        format: "S16_LE",
        sampleRate,
        channels: channelCount,
    };
    const player = aplay({
        ...options,
        bufferSize: aplayFrameSize,
    });

    encoder.setBitrate(48000);

    console.log("sample count is: %d", sampleCount);

    const ob = arecord({
        ...options,
        duration: 4,
    })
        .pipe(
            mergeMap(
                createRingBufferIterator(
                    new RingBuffer(sampleCount, Int16Array)
                )
            )
        )
        .pipe(
            mergeMap(
                encodeAsync({
                    encoder: encoder,
                    out: encoded,
                    sampleCount,
                }),
                1
            )
        )
        .pipe(
            mergeMap(
                decodeAsync({
                    decoder,
                    outPcm,
                    sampleCount,
                }),
                1
            )
        )
        .pipe(
            mergeMap(
                createRingBufferIterator(
                    new RingBuffer(aplayFrameSize, Uint8Array)
                )
            )
        )
        .pipe(mergeMap(sendToWritable(player.stdin), 1))
        .pipe(
            finalize(() => {
                player.stdin.end();
            })
        );

    return lastValueFrom(ob);
}

function sendToWritable(stream: Writable) {
    let maxByteLength = 0;
    return <T extends ITypedArray<T>>(pcm: T) =>
        new Observable<T>((s) => {
            const copy = Buffer.allocUnsafe(pcm.byteLength);
            copy.set(Buffer.from(pcm.buffer, pcm.byteOffset, pcm.byteLength));
            if (pcm.byteLength > maxByteLength) {
                console.log(
                    "bytes = %d, sample count = %d",
                    pcm.byteLength,
                    pcm.length
                );
                maxByteLength = pcm.byteLength;
            }
            const result = stream.write(copy, (err) => {
                if (err) {
                    s.error(err);
                } else {
                    s.next(pcm);
                    s.complete();
                }
            });
            assert.strict.ok(result);
        });
}

function createRingBufferIterator<T extends ITypedArray<T>>(
    ringBuffer: RingBuffer<T>
) {
    return (buffer: ITypedArray<unknown>) => {
        return new Observable<T>((s) => {
            ringBuffer.write(buffer);
            let inPcm: T | null = null;
            do {
                inPcm = ringBuffer.read();
                if (inPcm !== null) {
                    s.next(inPcm);
                }
            } while (inPcm !== null);
            s.complete();
        });
    };
}

function encodeAsync({
    encoder,
    out,
    sampleCount,
}: {
    encoder: opus.Encoder;
    out: Uint8Array;
    sampleCount: number;
}) {
    return (pcm: Int16Array) =>
        new Observable<Uint8Array>((s) => {
            encoder.encodeAsync(
                pcm,
                sampleCount,
                out,
                out.byteLength,
                (result) => {
                    if (typeof result === "string") {
                        s.error(`Failed to encode ${pcm.length}: ${result}`);
                    } else {
                        s.next(
                            out.subarray(
                                0,
                                result / Uint8Array.BYTES_PER_ELEMENT
                            )
                        );
                        s.complete();
                    }
                }
            );
        });
}

function decodeAsync({
    decoder,
    outPcm,
    sampleCount,
}: {
    decoder: opus.Decoder;
    outPcm: Int16Array;
    sampleCount: number;
}) {
    return (encoded: Uint8Array) =>
        new Observable<Int16Array>((s) => {
            decoder.decodeAsync(
                encoded,
                encoded.byteLength,
                outPcm,
                sampleCount,
                0,
                (sampleCount) => {
                    if (typeof sampleCount === "string") {
                        s.error(
                            `Failed to decode ${encoded.byteLength} bytes with error: ${sampleCount}`
                        );
                    } else {
                        s.next(outPcm.subarray(0, sampleCount));
                        s.complete();
                    }
                }
            );
        });
}

async function testRingBuffer() {
    const a1 = crypto.randomFillSync(new Int16Array(2800));
    const rb = new RingBuffer(2880, Int16Array);
    for (let i = 0; i < 100; i++) {
        rb.write(a1);
        assert.strict.equal(rb.read(), null);
        rb.write(new Int16Array(80));
        const givenResult = rb.read();
        const expectedResult = new Int16Array([...a1, ...new Int16Array(80)]);
        assert.strict.deepEqual(givenResult, expectedResult);
    }
}

async function test(fn: () => Promise<unknown>) {
    try {
        await fn();
        console.log("-- %s:", fn.name);
        console.log(chalk.green("\tsucceeded"));
    } catch (reason) {
        console.log(chalk.red("failed\n"));
        console.error(reason);
        throw new Exception("Test failed");
    } finally {
        console.log();
    }
}

const supportedFrameSizes = [2.5, 10, 20, 40, 60, 80, 100, 120];

(async () => {
    console.log(chalk.bgWhite(chalk.black("-- starting tests")));
    await test(testRingBuffer);
    await test(function testDecoderTest() {
        return testDecoder({
            frameSize: 120,
            sampleRate: 48000,
        });
    });
    await test(testOpusCodec);
    await test(createFile);
})().catch((reason) => {
    if (reason instanceof Exception) {
        console.error(reason.what());
    } else {
        console.error(reason);
    }
    process.exitCode = 1;
});
