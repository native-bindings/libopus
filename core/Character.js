"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Character {
    static isTab(ch) {
        return ch === 9;
    }
    static isLineBreak(ch) {
        return ch === 13 || ch === 10;
    }
    static isIdentifierPart(ch) {
        return Character.isIdentifierStart(ch) || Character.isIntegerPart(ch);
    }
    static isWhiteSpace(ch) {
        return ch === 32;
    }
    // "
    static isStringLiteralStart(ch) {
        return ch === 34;
    }
    // 0-9
    static isIntegerPart(ch) {
        return ch >= 48 && ch <= 57;
    }
    // 0-9 a-f A-F
    static isHexadecimalIntegerPart(ch) {
        return (Character.isIntegerPart(ch) || // 0-9
            (ch >= 97 && ch <= 102) || // a-f
            (ch >= 65 && ch <= 70) // A-F
        );
    }
    // a-z A-Z _
    static isIdentifierStart(ch) {
        return ((ch >= 97 && ch <= 122) || // a-z
            (ch >= 65 && ch <= 90) || // A-Z
            ch === 95 // _
        );
    }
}
exports.default = Character;
//# sourceMappingURL=Character.js.map