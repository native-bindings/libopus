import Exception from "./Exception";

export function lowerFirst(value: string) {
    return `${value[0]?.toLowerCase()}${value.substring(1)}`;
}

export function getMacroFunctionName(key: string) {
    return key.replace(/_REQUEST$/, "");
}

export function camelCase(key: string) {
    return key
        .toLowerCase()
        .replace(/^_?/, "")
        .replace(
            /([a-z])(_)([a-z])/g,
            (_0, a, _1, b) => `${a.toLowerCase()}${b.toUpperCase()}`
        );
}

export function getNativeMethodNameFromKey(key: string, keyPrefix: string) {
    if (!key.endsWith("_REQUEST")) {
        throw new Exception(`Expecting ${key} to end with _REQUEST`);
    }
    return upperFirst(
        camelCase(
            key.substring(keyPrefix.length - 1, key.length - "_REQUEST".length)
        )
    );
}

export function upperFirst(key: string) {
    return `${key[0]?.toUpperCase()}${key.substring(1)}`;
}
