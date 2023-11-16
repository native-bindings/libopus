export declare function mergeParsedArgumentsLine(line: IParsedArgumentsLine, other: IParsedArgumentsLine): IParsedArgumentsLine;
export interface IParsedArgumentsLine {
    remaining: string;
    includeDirectories: string[];
    searchDirectories: string[];
    libraries: string[];
}
export default function parseArgumentsLine(line: string): IParsedArgumentsLine;
//# sourceMappingURL=parseArgumentsLine.d.ts.map