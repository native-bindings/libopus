export class Encoder {
    constructor(sampleRate: number, channels: number, app: number);
    encode(pcm: Int16Array, frameSize: number, maxDataBytes: number): Buffer;
    encodeFloat(
        pcm: Float32Array,
        frameSize: number,
        data: Uint8Array,
        maxDataBytes: number
    ): number;
}
export class Decoder {
    constructor(sampleRate: number, channels: number);
    decode(pcm: Uint8Array, frameSize: number, decodeFec: number): Int16Array;
    decodeFloat(
        encoded: Uint8Array,
        encodedLength: number,
        pcmOut: Float32Array,
        frameSize: number,
        decodeFec: number
    ): number;
}

export namespace opusenc {
    class Encoder {
        constructor();
        createFile(
            comments: Comments,
            file: string,
            rate: number,
            channels: number,
            family: number
        ): void;
        // Write out the header now rather than wait for audio to begin.
        flushHeader(): void;
        /**
         * Create a new OggOpus stream to be used along with.ope_encoder_get_page().
         * This is mostly useful for muxing with other streams.
         */
        createPull(rate: number, channels: number, family: number): void;
        // Add/encode any number of float samples to the file.
        writeFloat(value: Float32Array, samples: number): void;
        // Add/encode any number of int16 samples to the file.
        write(value: Int16Array, samples: number): void;
        // Finalizes the stream, but does not deallocate the object.
        drain(): void;
        // Ends the stream and create a new file.
        continueNewFile(path: string, comments: Comments): void;
        /**
         * Deferred initialization of the encoder to force an explicit channel mapping. This can be used to override the default channel coupling,
         * but using it for regular surround will almost certainly lead to worse quality.
         */
        deferredInitWithMapping(
            family: number,
            streams: number,
            coupled_streams: number,
            mapping: Uint8Array
        ): void;
        getPage(flush: boolean): Uint8Array;
        chainCurrent(comments: Comments): void;
        /**
         * get information
         */
        setApplication(value: number): void;
        setBitrate(value: number): void;
        setMaxBandwidth(value: number): void;
        setVbr(value: number): void;
        setBandwidth(value: number): void;
        setComplexity(value: number): void;
        setInbandFec(value: number): void;
        setPacketLossPerc(value: number): void;
        setDtx(value: number): void;
        setVbrConstraint(value: number): void;
        setForceChannels(value: number): void;
        setSignal(value: number): void;
        setLsbDepth(value: number): void;
        setExpertFrameDuration(value: number): void;
        setPredictionDisabled(value: number): void;
        setPhaseInversionDisabled(value: number): void;

        getApplication(): number;
        getBitrate(): number;
        getMaxBandwidth(): number;
        getVbr(): number;
        getBandwidth(): number;
        getComplexity(): number;
        getInbandFec(): number;
        getPacketLossPerc(): number;
        getDtx(): number;
        getVbrConstraint(): number;
        getForceChannels(): number;
        getSignal(): number;
        getLsbDepth(): number;
        getPredictionDisabled(): number;
    }
    export class Comments {
        add(key: string, tag: string): void;
    }
}

export { default as constants } from "./constants";
