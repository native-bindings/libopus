export function mergeParsedArgumentsLine(
    line: IParsedArgumentsLine,
    other: IParsedArgumentsLine
): IParsedArgumentsLine {
    return {
        remaining: line.remaining + " " + other.remaining,
        includeDirectories: line.includeDirectories.concat(
            other.includeDirectories
        ),
        searchDirectories: line.searchDirectories.concat(
            other.searchDirectories
        ),
        libraries: line.libraries.concat(other.libraries),
    };
}

export interface IParsedArgumentsLine {
    remaining: string;
    includeDirectories: string[];
    searchDirectories: string[];
    libraries: string[];
}

export default function parseArgumentsLine(line: string): IParsedArgumentsLine {
    interface IArgumentRange {
        start: number;
        end: number;
    }
    const searchDirectories = new Array<string>();
    const includeDirectories = new Array<string>();
    const libraries = new Array<string>();
    const positions = new Array<IArgumentRange>();
    for (let i = 0; i < line.length; i++) {
        const remaining = line.substring(i);
        const isLinkDirectory = remaining.startsWith("-L");
        const isIncludeDirectory = remaining.startsWith("-I");
        const isLibrary = remaining.startsWith("-l");
        if (isLinkDirectory || isIncludeDirectory || isLibrary) {
            const start = i;
            i += 2;
            const lineStart = i;
            for (let j = lineStart; j < line.length; j++) {
                /**
                 * break on space
                 */
                if (line[j] === " ") {
                    i = j;
                    break;
                }
                /**
                 * break on end of line
                 */
                if (j === line.length - 1) {
                    i = j + 1;
                    break;
                }
            }
            const result = line.substring(lineStart, i);
            positions.push({
                start: start,
                end: i,
            });
            if (isLibrary) {
                libraries.push(result);
            } else if (isLinkDirectory) {
                searchDirectories.push(result);
            } else if (isIncludeDirectory) {
                includeDirectories.push(result);
            }
        }
    }
    let diff = 0;
    let remaining = line;
    for (const pos of positions) {
        const newRemaining =
            remaining.substring(0, diff + pos.start) +
            remaining.substring(diff + pos.end);
        diff += newRemaining.length - remaining.length;
        remaining = newRemaining;
    }
    return {
        remaining,
        includeDirectories,
        searchDirectories,
        libraries,
    };
}
