import { ILibrary } from "./Compiler";
export default class InterfaceLibrariesGenerator {
    private readonly librariesDirectory;
    constructor(librariesDirectory: string);
    generateInterfaceLibraries(inputLibraries: ILibrary[]): Promise<void>;
}
//# sourceMappingURL=InterfaceLibrariesGenerator.d.ts.map