export interface ITypedArray<T = unknown> {
    length: number;
    buffer: ArrayBufferLike;
    byteOffset: number;
    byteLength: number;
    slice(start: number, end: number): T;
    subarray(start: number, end: number): T;
    /**
     * Sets a value or an array of values.
     * @param array A typed or untyped array of values to set.
     * @param offset The index in the current array at which the values are to be written.
     */
    set(array: T, offset?: number): void;
}

interface TypedArrayConstructor<T extends ITypedArray> {
    new (length: number): T;
    new (buffer: ArrayBufferLike): T;
    new (buffer: ArrayBufferLike, byteOffset: number, length: number): T;
    BYTES_PER_ELEMENT: number;
}

export default class RingBuffer<T extends ITypedArray<T>> {
    #arrayBuffer;
    #readOffset;
    #writeOffset;
    #frameSize;
    #ArrayBufferConstructor;
    #TypedArrayConstructor;
    public constructor(
        /**
         * frame size in sample count
         */
        frameSize: number,
        TypedArrayConstructor: TypedArrayConstructor<T>,
        ArrayBufferConstructor: new (
            length: number
        ) => ArrayBufferLike = ArrayBuffer
    ) {
        this.#readOffset = 0;
        this.#writeOffset = 0;
        this.#TypedArrayConstructor = TypedArrayConstructor;
        this.#ArrayBufferConstructor = ArrayBufferConstructor;
        this.#arrayBuffer = new this.#ArrayBufferConstructor(
            this.#initialSize()
        );
        this.#frameSize = frameSize;
    }
    public write(value: ITypedArray) {
        const out = new this.#TypedArrayConstructor(
            value.buffer,
            value.byteOffset,
            value.byteLength / this.#TypedArrayConstructor.BYTES_PER_ELEMENT
        );
        this.#maybeReallocate(out.length);
        this.#view().set(out, this.#writeOffset);
        this.#writeOffset += out.length;
    }
    public drain() {
        return this.#read(this.#writeOffset - this.#readOffset);
    }
    public read(): T | null {
        return this.#read(this.#frameSize);
    }
    #view() {
        return new this.#TypedArrayConstructor(this.#arrayBuffer);
    }
    #read(sampleCount: number): T | null {
        if (!sampleCount) {
            return null;
        }
        const remainingBytes = this.#writeOffset - this.#readOffset;
        if (remainingBytes >= sampleCount) {
            const view = this.#view().subarray(
                this.#readOffset,
                this.#readOffset + sampleCount
            );
            this.#readOffset += sampleCount;
            if (this.#readOffset >= this.#writeOffset) {
                this.#writeOffset = 0;
                this.#readOffset = 0;
            }
            return view;
        }
        return null;
    }
    #maybeReallocate(samples: number) {
        const sampleCountInBytes =
            samples * this.#TypedArrayConstructor.BYTES_PER_ELEMENT;
        if (this.#view().length - this.#writeOffset <= samples) {
            const oldArrayBuffer = this.#arrayBuffer;
            this.#arrayBuffer = new this.#ArrayBufferConstructor(
                oldArrayBuffer.byteLength +
                    sampleCountInBytes +
                    this.#initialSize()
            );
            this.#view().set(new this.#TypedArrayConstructor(oldArrayBuffer));
        }
    }
    #initialSize() {
        return (
            this.#frameSize * this.#TypedArrayConstructor.BYTES_PER_ELEMENT * 2
        );
    }
}
