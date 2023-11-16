"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Exception {
    what;
    stack;
    constructor(what, stack = null) {
        this.what = what;
        this.stack = stack;
        Error.captureStackTrace(this, Exception);
    }
}
exports.default = Exception;
//# sourceMappingURL=Exception.js.map