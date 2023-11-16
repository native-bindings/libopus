export default class Character {
    static isTab(ch: number) {
        return ch === 9;
    }
    static isLineBreak(ch: number) {
        return ch === 13 || ch === 10;
    }
    static isIdentifierPart(ch: number) {
        return Character.isIdentifierStart(ch) || Character.isIntegerPart(ch);
    }
    static isWhiteSpace(ch: number) {
        return ch === 32;
    }
    // "
    static isStringLiteralStart(ch: number) {
        return ch === 34;
    }
    // 0-9
    static isIntegerPart(ch: number) {
        return ch >= 48 && ch <= 57;
    }
    // 0-9 a-f A-F
    static isHexadecimalIntegerPart(ch: number) {
        return (
            Character.isIntegerPart(ch) || // 0-9
            (ch >= 97 && ch <= 102) || // a-f
            (ch >= 65 && ch <= 70) // A-F
        );
    }
    // a-z A-Z _
    static isIdentifierStart(ch: number) {
        return (
            (ch >= 97 && ch <= 122) || // a-z
            (ch >= 65 && ch <= 90) || // A-Z
            ch === 95 // _
        );
    }
}
