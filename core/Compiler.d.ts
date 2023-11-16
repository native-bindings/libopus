export interface ILibrary {
    sourceDir: string;
}
/**
 * A class made to compile Makefile or CMake projects and turn them into an interface library
 * for the Node.js bindings CMake project.
 */
export default class Compiler {
    #private;
    private readonly librariesDirectory;
    private readonly libraries;
    constructor(librariesDirectory: string, libraries: ILibrary[]);
    compile({ configure }: {
        configure: boolean;
    }): Promise<void>;
}
//# sourceMappingURL=Compiler.d.ts.map