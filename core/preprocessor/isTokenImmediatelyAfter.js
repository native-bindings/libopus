"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
/**
 * Checks if the first token is immediately after the second token
 * @param a token that should be immediately before
 * @param b token that should be immediately after
 * @returns true if the first token is immediately after the second token, false otherwise
 */
function isTokenImmediatelyAfter(a, b) {
    return a.position.start === b.position.end;
}
exports.default = isTokenImmediatelyAfter;
//# sourceMappingURL=isTokenImmediatelyAfter.js.map