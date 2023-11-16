import ErrorFormatter from "./ErrorFormatter";
export interface IRange {
    start: number;
    end: number;
}
/**
 * This class will mark a position in the reader.
 * It can return a range from the marked position to the current position when range() is called.
 */
export default class RangeFactory {
    #private;
    constructor({ errorFormatter, position }: {
        errorFormatter: ErrorFormatter;
        position: () => number;
    });
    /**
     * Mark the current position. if a position is already marked, an exception will be thrown
     */
    mark(): void;
    /**
     * Reset the marked position. if no position is marked, an exception will be thrown
     */
    reset(): void;
    /**
     * Get a range from the marked position to the current position
     */
    range(): IRange;
}
//# sourceMappingURL=RangeFactory.d.ts.map