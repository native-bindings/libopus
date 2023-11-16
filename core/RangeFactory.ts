import ErrorFormatter from "./ErrorFormatter";
import Exception from "./Exception";

export interface IRange {
    start: number;
    end: number;
}

/**
 * This class will mark a position in the reader.
 * It can return a range from the marked position to the current position when range() is called.
 */
export default class RangeFactory {
    readonly #errorFormatter;
    readonly #position;
    #markedPosition: number | null = null;
    public constructor({
        errorFormatter,
        position
    }: {
        errorFormatter: ErrorFormatter;
        position: () => number;
    }) {
        this.#position = position;
        this.#errorFormatter = errorFormatter;
    }
    /**
     * Mark the current position. if a position is already marked, an exception will be thrown
     */
    public mark() {
        if (this.#markedPosition !== null) {
            throw new Exception(
                this.#errorFormatter.format(`Position is already marked`)
            );
        }
        this.#markedPosition = this.#position();
    }
    /**
     * Reset the marked position. if no position is marked, an exception will be thrown
     */
    public reset() {
        if (this.#markedPosition === null) {
            throw new Exception(
                this.#errorFormatter.format(
                    `Tried to reset RangeFactory instance, but position is not marked`
                )
            );
        }
        this.#markedPosition = null;
    }
    /**
     * Get a range from the marked position to the current position
     */
    public range() {
        if (this.#markedPosition === null) {
            throw new Exception(
                this.#errorFormatter.format(
                    `mark() must be called before calling range()`
                )
            );
        }
        if (this.#markedPosition === this.#position()) {
            throw new Exception(
                this.#errorFormatter.format(
                    `mark() was called, but range() was called while no characters were consumed`
                )
            );
        }
        const range: IRange = {
            start: this.#markedPosition,
            end: this.#position()
        };
        this.#markedPosition = null;
        return range;
    }
}
