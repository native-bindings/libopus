export default class Exception {
    readonly #what;
    public constructor(what: string) {
        this.#what = what;
    }
    public what() {
        return this.#what;
    }
    public toString() {
        return this.what();
    }
}
