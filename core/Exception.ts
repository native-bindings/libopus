export default class Exception {
    public constructor(
        public readonly what: string,
        public stack: string | null = null
    ) {
        Error.captureStackTrace(this, Exception);
    }
}
