interface IBaseTypedArray extends ArrayLike<number> {
    set(value: IBaseTypedArray): void;
    length: number;
}

export function createTypedArrayCloner<T extends IBaseTypedArray>(
    TypedArrayConstructor: new (length: number) => T
) {
    return (value: T) => {
        const l = new TypedArrayConstructor(value.length);
        l.set(value);
        return l;
    };
}

export class Converter {
    #sampleRate;
    public constructor(sampleRate: number) {
        this.#sampleRate = sampleRate;
    }
    public frameSizeToByteLength(ms: number) {
        return ms * (this.#sampleRate / 1000);
    }
    public byteLengthToFrameSize(byteLength: number) {
        return byteLength / (this.#sampleRate / 1000);
    }
}

export const cloneUint8Array = createTypedArrayCloner(Uint8Array);

export const cloneInt16Array = createTypedArrayCloner(Int16Array);
