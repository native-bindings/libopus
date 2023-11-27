export default function capitalize(value: string) {
    return value.split('').map((char, index) => {
        return index === 0 ? char.toUpperCase() : char.toLowerCase();
    }).join('');
}