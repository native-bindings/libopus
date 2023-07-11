import child_process from "child_process";
import { Observable, finalize } from "rxjs";
import Exception from "./Exception";
import assert from "assert";

class InvalidChildProcessExitCode extends Exception {
    public constructor(code: number | null) {
        super(`Process exited with invalid code: ${code}`);
    }
}

type Format =
    | "S8"
    | "U8"
    | "S16_LE"
    | "S16_BE"
    | "U16_LE"
    | "U16_BE"
    | "S24_LE"
    | "S24_BE"
    | "U24_LE"
    | "U24_BE"
    | "S32_LE"
    | "S32_BE"
    | "U32_LE"
    | "U32_BE"
    | "FLOAT_LE"
    | "FLOAT_BE"
    | "FLOAT64_LE"
    | "FLOAT64_BE"
    | "IEC958_SUBFRAME_LE"
    | "IEC958_SUBFRAME_BE"
    | "MU_LAW"
    | "A_LAW"
    | "IMA_ADPCM"
    | "MPEG"
    | "GSM"
    | "S20_LE"
    | "S20_BE"
    | "U20_LE"
    | "U20_BE"
    | "SPECIAL"
    | "S24_3LE"
    | "S24_3BE"
    | "U24_3LE"
    | "U24_3BE"
    | "S20_3LE"
    | "S20_3BE"
    | "U20_3LE"
    | "U20_3BE"
    | "S18_3LE"
    | "S18_3BE"
    | "U18_3LE"
    | "U18_3BE"
    | "G723_24"
    | "G723_24_1B"
    | "G723_40"
    | "G723_40_1B"
    | "DSD_U8"
    | "DSD_U16_LE"
    | "DSD_U32_LE"
    | "DSD_U16_BE"
    | "DSD_U32_BE";

export interface IOptions {
    format: Format;
    channels: number;
    bufferSize?: number;
    sampleRate: number;
    duration?: number;
}

function optionsToArgList({
    format,
    channels,
    duration,
    bufferSize,
    sampleRate,
}: IOptions) {
    const args: string[] = [
        "--disable-resample",
        "--disable-softvol",
        "--disable-format",
        "-t",
        "raw",
        "-r",
        `${sampleRate}`,
        "-c",
        `${channels}`,
        "-f",
        `${format}`,
    ];
    if (typeof bufferSize !== "undefined") {
        args.push(`--buffer-size=${bufferSize}`);
    }
    if (typeof duration !== "undefined") {
        args.push("-d", `${duration}`);
    }
    return args;
}

export function aplay(options: IOptions) {
    console.log("$ %s %s", "aplay", optionsToArgList(options).join(" "));
    return child_process.spawn("aplay", optionsToArgList(options));
}

export function arecord(options: IOptions) {
    const pcm = child_process.spawn("arecord", optionsToArgList(options));
    console.log("$ %s %s", "arecord", optionsToArgList(options).join(" "));
    return new Observable<Buffer>((s) => {
        pcm.stdout.on("data", (chunk) => {
            assert.strict.ok(Buffer.isBuffer(chunk));
            s.next(chunk);
        });
        pcm.on("exit", (code) => {
            if (code !== 0) {
                s.error(new InvalidChildProcessExitCode(code));
            } else {
                s.complete();
            }
        });
    }).pipe(
        finalize(() => {
            pcm.kill(0);
        })
    );
}
