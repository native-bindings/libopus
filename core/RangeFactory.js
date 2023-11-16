"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const Exception_1 = __importDefault(require("./Exception"));
/**
 * This class will mark a position in the reader.
 * It can return a range from the marked position to the current position when range() is called.
 */
class RangeFactory {
    #errorFormatter;
    #position;
    #markedPosition = null;
    constructor({ errorFormatter, position }) {
        this.#position = position;
        this.#errorFormatter = errorFormatter;
    }
    /**
     * Mark the current position. if a position is already marked, an exception will be thrown
     */
    mark() {
        if (this.#markedPosition !== null) {
            throw new Exception_1.default(this.#errorFormatter.format(`Position is already marked`));
        }
        this.#markedPosition = this.#position();
    }
    /**
     * Reset the marked position. if no position is marked, an exception will be thrown
     */
    reset() {
        if (this.#markedPosition === null) {
            throw new Exception_1.default(this.#errorFormatter.format(`Tried to reset RangeFactory instance, but position is not marked`));
        }
        this.#markedPosition = null;
    }
    /**
     * Get a range from the marked position to the current position
     */
    range() {
        if (this.#markedPosition === null) {
            throw new Exception_1.default(this.#errorFormatter.format(`mark() must be called before calling range()`));
        }
        if (this.#markedPosition === this.#position()) {
            throw new Exception_1.default(this.#errorFormatter.format(`mark() was called, but range() was called while no characters were consumed`));
        }
        const range = {
            start: this.#markedPosition,
            end: this.#position()
        };
        this.#markedPosition = null;
        return range;
    }
}
exports.default = RangeFactory;
//# sourceMappingURL=RangeFactory.js.map