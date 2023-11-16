export default function decodeText(value: Uint8Array) {
    return new TextDecoder().decode(value);
}
