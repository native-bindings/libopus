import opus, { OpusFile } from "..";
import path from "path";
import fs from "fs";
import test from "ava";
import { concatMap, from, map, of, range, throwError } from "rxjs";

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
                map((result) => new Float32Array(result.buffer.buffer))
            );
        })
    );
}

test("opus/Encoder", async (t) => {
    const enc = new opus.Encoder(
        48000,
        1,
        opus.constants.OPUS_APPLICATION_VOIP
    );
    const opusFrames = (
        await stream(path.resolve(__dirname, "f32le_48000_1_10.bin"), 2880)
    ).pipe(
        map((samples) => {
            const length = enc.encodeFloat(samples, 2880, out, out.byteLength);
            return out.slice(0, length);
        })
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
                0
            );

            t.deepEqual(decoded, 2880);
        },
    });

    return new Promise((resolve) =>
        sub.add(() => {
            resolve();
        })
    );
});

test("opusfile/OpusFile/openFile", (t) => {
    const of = new OpusFile();
    of.openFile(path.resolve(__dirname, "sample-3.opus"));
    const pcm = new Float32Array(2880);
    t.deepEqual(of.pcmTell(), 0);
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), 648);
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), 1608);
    t.deepEqual(of.pcmSeek(0), undefined);
    t.deepEqual(of.pcmTell(), 0);
    t.deepEqual(of.readFloat(pcm), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.channelCount(0), 2);
    t.deepEqual(of.channelCount(1), 2);
    t.deepEqual(of.linkCount(), 1);
    t.deepEqual(of.rawTotal(0), 705632);
});

test("opusenc/Encoder/createPull", async (t) => {
    const enc = new opus.opusenc.Encoder();
    const comments = new opus.opusenc.Comments();
    enc.createPull(comments, 48000, 1, 0);
    const duration = 4;
    const fd = await fs.promises.open(
        path.resolve(__dirname, "f32le_48000_1_10.bin")
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
    t.deepEqual(of.pcmTotal(-1), 480000);
    t.deepEqual(of.pcmTell(), 0);
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 648,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), 648);
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), 1608);
    t.deepEqual(of.readFloat(frame), {
        sampleCount: 960,
        linkIndex: 0,
    });
    t.deepEqual(of.pcmTell(), 2568);
});
