import opus, { OpusFile } from "..";
import path from "path";
import fs from "fs";
import test from "ava";
import { concatMap, from, map, of, range, throwError } from "rxjs";
import * as math from "mathjs";
import assert from "assert";

const frequencyMap = {
    A: 440,
    "A#": 466.16,
    Bb: 466.16,
    B: 493.88,
    Cb: 493.88,
    C: 261.63,
    "C#": 277.18,
    Db: 277.18,
    D: 293.66,
    "D#": 311.13,
    Eb: 311.13,
    E: 329.63,
    Fb: 329.63,
    "E#": 349.23,
    F: 349.23,
    "F#": 369.99,
    Gb: 369.99,
    G: 392.0,
    "G#": 415.3,
    Ab: 415.3,
};

function generateNote(
    note: keyof typeof frequencyMap,
    durationMillis: number,
    sampleRate: number,
): Float32Array {
    if (!frequencyMap[note]) {
        throw new Error(`Invalid note: ${note}`);
    }

    const angularFrequency = 2 * Math.PI * frequencyMap[note];

    // Convert duration from milliseconds to seconds
    const durationSeconds = durationMillis / 1000;

    // Calculate the number of samples
    const numSamples = Math.round(durationSeconds * sampleRate);

    const arr = new Float32Array(numSamples);

    for (let i = 0; i < numSamples; ++i) {
        arr[i] = Math.sin((angularFrequency * i) / sampleRate);
    }

    return arr;
}

async function stream(pcmFile: string, frameSize: number) {
    const fd = await fs.promises.open(pcmFile);
    const pcm = new Uint8Array(frameSize * Float32Array.BYTES_PER_ELEMENT);
    const totalFileSize = (await fd.stat()).size;
    const partSize = frameSize * Float32Array.BYTES_PER_ELEMENT;
    const parts = Math.ceil(totalFileSize / partSize);
    return range(0, parts).pipe(
        concatMap((part) => {
            const offset = part * partSize;
            return from(fd.read(pcm, 0, pcm.length, offset)).pipe(
                concatMap((result) => {
                    if (result.bytesRead > 0) {
                        return of(result);
                    }
                    return throwError(() => new Error("EOF"));
                }),
                map((result) => new Float32Array(result.buffer.buffer)),
            );
        }),
    );
}

function findDominantFrequency(pcmData: Float32Array, sampleRate: number) {
    const phasors = math.fft(Array.from(pcmData));
    const magnitudes = phasors.map((phasor) => math.abs(phasor));

    let maxIndex = magnitudes.reduce((iMax, x, i, arr) => {
        const n = arr[iMax];
        assert.strict.ok(typeof n !== "undefined", `n is undefined`);
        return math.larger(x, n) ? i : iMax;
    }, 0);

    // Perform Quadratic Interpolation
    const preciseFrequency = interpolateFrequency(
        magnitudes,
        maxIndex,
        sampleRate,
        pcmData.length,
    );

    return preciseFrequency;
}

function interpolateFrequency(
    magnitudes: number[],
    index: number,
    sampleRate: number,
    N: number,
) {
    const alpha = magnitudes[index - 1];
    const beta = magnitudes[index];
    const gamma = magnitudes[index + 1];

    assert.strict.ok(
        typeof alpha !== "undefined" &&
            typeof beta !== "undefined" &&
            typeof gamma !== "undefined",
        `alpha is undefined for index ${index}`,
    );

    const improvedIndex =
        index + (0.5 * (alpha - gamma)) / (alpha - 2 * beta + gamma);

    return (improvedIndex * sampleRate) / N;
}

/**
 * Opus frame duration in milliseconds
 */
type OpusFrameDuration = 2.5 | 5 | 10 | 20 | 40 | 60;

function sampleCount(sampleRate: number, duration: OpusFrameDuration) {
    return (sampleRate / 1000) * duration;
}

test("opus/Decoder to output somewhat precise frequency using the data created by opus/Encoder class", async (t) => {
    const rate = 48000;
    const frameDuration: OpusFrameDuration = 60;
    const encoder = new opus.Encoder(
        rate,
        1,
        opus.constants.OPUS_APPLICATION_AUDIO,
    );
    type Note = keyof typeof frequencyMap;
    const notes: Note[] = ["A", "B", "C", "D", "E", "F", "G"];
    const decoder = new opus.Decoder(rate, 1);
    const encoded = new Uint8Array(1024 * 1024 * 2);
    const pcm = new Float32Array(sampleCount(rate, frameDuration));
    for (const noteKey of notes) {
        const original = generateNote(noteKey, frameDuration, rate);
        const expectedFrequencies = [
            frequencyMap[noteKey] - 3,
            frequencyMap[noteKey] - 2,
            frequencyMap[noteKey] - 1,
            frequencyMap[noteKey],
            frequencyMap[noteKey] + 1,
            frequencyMap[noteKey] + 2,
            frequencyMap[noteKey] + 3,
            frequencyMap[noteKey] + 4,
            frequencyMap[noteKey] + 5,
        ];
        const pageByteLength = encoder.encodeFloat(
            original,
            original.length,
            encoded,
            encoded.byteLength,
        );
        const decodedSampleCount = decoder.decodeFloat(
            encoded,
            pageByteLength,
            pcm,
            pcm.length,
            0,
        );
        const calculatedFrequency = findDominantFrequency(pcm, rate);
        t.deepEqual(decodedSampleCount, sampleCount(rate, frameDuration));
        t.assert(
            expectedFrequencies.some(
                (freq) => Math.round(freq) === Math.round(calculatedFrequency),
            ),
            `Expected ${noteKey} to be one of "${expectedFrequencies.join(
                ", ",
            )}", but got ${calculatedFrequency} instead.`,
        );
    }
});

test("opus/Encoder", async (t) => {
    const enc = new opus.Encoder(
        48000,
        1,
        opus.constants.OPUS_APPLICATION_VOIP,
    );
    const opusFrames = (
        await stream(path.resolve(__dirname, "f32le_48000_1_10.bin"), 2880)
    ).pipe(
        map((samples) => {
            const length = enc.encodeFloat(samples, 2880, out, out.byteLength);
            return out.slice(0, length);
        }),
    );

    const out = new Uint8Array(1024 * 1024 * 2);

    const decoder = new opus.Decoder(48000, 1);

    const sub = opusFrames.subscribe({
        next(opusFrame) {
            const out = new Float32Array(2880);
            const decoded = decoder.decodeFloat(
                opusFrame,
                opusFrame.byteLength,
                out,
                2880,
                0,
            );

            t.deepEqual(decoded, 2880);
        },
    });

    return new Promise((resolve) =>
        sub.add(() => {
            resolve();
        }),
    );
});

test("opusfile/OpusFile/openFile", (t) => {
    const of = new OpusFile();
    of.openFile(path.resolve(__dirname, "sample-3.opus"));
    const pcm = new Float32Array(2880);
    t.deepEqual(of.pcmTell(), "0");
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), "648");
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), "1608");
    t.deepEqual(of.pcmSeek("0"), undefined);
    t.deepEqual(of.pcmTell(), "0");
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.channelCount(0), 2);
    t.deepEqual(of.channelCount(1), 2);
    t.deepEqual(of.linkCount(), 1);
    t.deepEqual(of.rawTotal(0), "705632");
});

test("opusenc/Encoder/createPull", async (t) => {
    const enc = new opus.opusenc.Encoder();
    const comments = new opus.opusenc.Comments();
    enc.createPull(comments, 48000, 1, 0);
    const duration = 4;
    const fd = await fs.promises.open(
        path.resolve(__dirname, "f32le_48000_1_10.bin"),
    );
    const opusFile = new Array<Uint8Array>();
    const totalFileSize = (await fd.stat()).size;
    const totalSampleCount = totalFileSize / Float32Array.BYTES_PER_ELEMENT;
    const frameSize = totalSampleCount / (duration * 32);
    const readPages = async (flush: boolean) => {
        let page = enc.getPage(flush);
        do {
            if (page !== null) {
                opusFile.push(page);
            }
            page = enc.getPage(flush);
        } while (page !== null);
    };
    const partSize = frameSize * Float32Array.BYTES_PER_ELEMENT;
    const parts = Math.ceil(totalFileSize / partSize);
    const pcm = new Uint8Array(frameSize * Float32Array.BYTES_PER_ELEMENT);
    for (let i = 0; i < parts; i++) {
        const offset = i * partSize;
        const result = await fd.read(pcm, 0, pcm.length, offset);
        t.assert(result.bytesRead > 0);
        const samples = new Float32Array(result.buffer.buffer);
        enc.writeFloat(samples, samples.length);
        await readPages(false);
    }
    enc.drain();
    await readPages(true);
    await fd.close();

    /**
     * test the generated opus file
     */
    const of = new OpusFile();
    const frame = new Float32Array(48000);
    of.openMemory(Buffer.concat(opusFile));
    t.deepEqual(of.pcmTotal(-1), "480000");
    t.deepEqual(of.pcmTell(), "0");
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), "648");
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), "1608");
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), "2568");
});
