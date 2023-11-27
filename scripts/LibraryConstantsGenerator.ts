import CodeStream from "textstreamjs";
import {
    INodeDefineMacroDirective,
    PreprocessorNode,
    PreprocessorNodeType,
} from "../core/preprocessor/PreprocessorParser";
import Exception from "./Exception";
import fs from "fs";
import path from "path";
import { lowerFirst } from "./helpers";
import capitalize from "./capitalize";

function transformToSnakeUpperCase(input: string): string {
    return (
        input
            // Insert an underscore before each capital letter
            .replace(/([A-Z])/g, "_$1")
            // Convert the entire string to uppercase
            .toUpperCase()
            // Trim the leading underscore if present
            .replace(/^_/, "")
    );
}

interface IConstantGroup {
    /**
     * suffix after the OPUS_ or OPE_ prefix
     */
    suffix: string;
    values: {
        name: string;
        value: number;
    }[];
    /**
     * current value
     */
    currentValue: number;
    prefix: string;
    className: string;
    setConstantsMethodName: string;
}

interface IGetterOrSetter {
    type: "GET" | "SET";
    memberName: string;
    macroName: string;
}

export default class LibraryConstantsGenerator extends CodeStream {
    readonly #textDecoder = new TextDecoder();
    readonly #macroNodeByName = new Map<string, INodeDefineMacroDirective>();
    readonly #constantGroups = new Map<string, IConstantGroup>();
    readonly #allowedConstantSuffixes = [
        "APPLICATION",
        "BANDWIDTH",
        "FRAMESIZE",
    ];
    readonly #privateOpusOptions = [
        "VOICE_RATIO",
        "FORCE_MODE",
        "LFE",
        "ENERGY_MASK",
    ];
    readonly #defineNodes = new Map<string, INodeDefineMacroDirective>();
    readonly #gettersAndSetters = new Map<
        INodeDefineMacroDirective,
        IGetterOrSetter
    >();
    readonly #files = new Map<string, string>();
    readonly #constantValueNativeType = "std::int32_t";
    public constructor() {
        super(undefined, {
            indentationSize: 4,
        });
    }
    /**
     * This function is supposed to be called several times with different node lists from different
     * header files.
     * @param nodes node list
     */
    public process(nodes: PreprocessorNode[]) {
        for (const node of nodes) {
            this.#processNode(node);
        }
    }
    public async generate() {
        this.#createConstantGroups();
        // if(!this.#gettersAndSetters.size) {
        //     return;
        // }
        this.#generateConstantsFiles();
        const nativeTypes = [
            {
                test: ["OPUS_GET_FINAL_RANGE"],
                type: "opus_uint32",
            },
            {
                test: null,
                type: "opus_int32",
            },
        ];
        for (const itemInfo of [
            {
                className: "EncoderBase",
                error: {
                    successValue: "OPUS_OK",
                    memberName: "result",
                    toStringFunction: "opus_strerror",
                    type: "int",
                },
                instanceName: "encoder",
                includeHeaders: ["<opus.h>"],
                namespace: "bindings",
                libraryInstanceType: "OpusEncoder",
                outDir: path.resolve(__dirname, "../src"),
                functionName: "opus_encoder_ctl",
            },
            {
                includeHeaders: ["<opus.h>"],
                instanceName: "decoder",
                namespace: "bindings",
                error: {
                    successValue: "OPUS_OK",
                    toStringFunction: "opus_strerror",
                    memberName: "result",
                    type: "int",
                },
                libraryInstanceType: "OpusDecoder",
                outDir: path.resolve(__dirname, "../src"),
                functionName: "opus_decoder_ctl",
                className: "DecoderBase",
            },
            {
                includeHeaders: ["<opusenc.h>"],
                className: "EncoderBase",
                instanceName: "encoder",
                error: {
                    successValue: "OPE_OK",
                    toStringFunction: "ope_strerror",
                    memberName: "result",
                    type: "int",
                },
                namespace: "bindings::opusenc",
                libraryInstanceType: "OggOpusEnc",
                outDir: path.resolve(__dirname, "../src/opusenc"),
                functionName: "ope_encoder_ctl",
            },
        ]) {
            const {
                includeHeaders,
                functionName,
                namespace,
                libraryInstanceType,
                instanceName,
                error,
                className,
                outDir,
            } = itemInfo;
            const headerId = `NATIVE_BINDINGS_OPUS_${transformToSnakeUpperCase(
                className,
            )}_H_`;
            this.write(`#ifndef ${headerId}\n`);
            this.write(`#define ${headerId}\n\n`);
            this.write(`#include <nan.h>\n\n`);
            for (const header of includeHeaders) {
                this.write(`#include ${header}\n`);
                if (header !== includeHeaders[includeHeaders.length - 1]) {
                    this.append("\n");
                }
            }
            /**
             * declare namespace
             */
            const getSettersAndSettersMemberName = `SetGettersAndSettersPrototypeMethods`;
            this.write(`namespace ${namespace} {\n\n`);
            this.write(`class ${className} : public Nan::ObjectWrap {\n`);
            this.write(`public:\n`);
            this.indentBlock(() => {
                this.write(`${libraryInstanceType}* value;\n`);
                this.write(`${error.type} ${error.memberName};\n`);
                this.write(
                    `static constexpr const char* ClassName = "${className}";\n`,
                );
                this.write(
                    `explicit ${className}(${libraryInstanceType}* value = nullptr);\n`,
                );
                this.write(`~${className}() override;\n`);
                this.write(
                    `static void ${getSettersAndSettersMemberName}(v8::Local<v8::FunctionTemplate> tpl);\n`,
                );
            });
            this.write("};\n");
            this.write("\n");
            this.write(`} // ${namespace}\n`);
            this.write(`#endif // ${headerId}\n`);
            this.#files.set(
                path.resolve(outDir, `${className}.h`),
                this.value(),
            );

            this.write('#include "core/Arguments.h"\n');
            this.write(`#include "${className}.h"\n`);
            this.write("\n");
            /**
             * use namespace to avoid having to reference it in the code
             */
            this.write(`using namespace ${namespace};\n\n`);
            this.write(
                `${className}::${className}(${libraryInstanceType}* value): value(value), ${error.memberName}(${error.successValue}) {}\n\n`,
            );
            this.write(`${className}::~${className}() {}\n\n`);
            for (const [, { type, memberName: member, macroName }] of this
                .#gettersAndSetters) {
                const nativeType = nativeTypes.find(({ test }) => {
                    if (test === null) {
                        return true;
                    }
                    return test.includes(macroName);
                })?.type;
                if (typeof nativeType === "undefined") {
                    throw new Exception(
                        `Could not find native type for ${macroName}`,
                    );
                }
                this.write(
                    `static NAN_METHOD(${member}) {\n`,
                    () => {
                        this.write(
                            `const Arguments args(info, "${member}");\n`,
                        );
                        this.write(`${className}* ${instanceName};\n`);
                        this.write(
                            `if(!args.Unwrap(${instanceName})) {\n`,
                            () => {
                                this.write("return;\n");
                            },
                            "}\n",
                        );
                        const finalArguments = new Array<string>();
                        const macro = this.#macroNodeByName.get(macroName);
                        if (typeof macro === "undefined") {
                            throw new Exception(
                                `Could not find macro ${macroName}`,
                            );
                        }
                        switch (type) {
                            case "GET":
                                this.write(`${nativeType} result;\n`);
                                finalArguments.push(`&result`);
                                break;
                            case "SET": {
                                const [arg] = macro.arguments;
                                if (
                                    typeof arg === "undefined" ||
                                    macro.arguments.length !== 1
                                ) {
                                    throw new Exception(
                                        `Invalid number of arguments for ${macroName}`,
                                    );
                                }
                                const name = new TextDecoder().decode(
                                    arg.value,
                                );
                                this.write(`${nativeType} ${name};\n`);
                                this.write(
                                    `if(!args.Convert(0, ${name})) {\n`,
                                    () => {
                                        this.write("return;\n");
                                    },
                                    "}\n",
                                );
                                finalArguments.push(`${name}`);
                                break;
                            }
                        }
                        this.write(
                            `auto& status = ${instanceName}->${error.memberName};\n`,
                        );
                        this.write(
                            `status = ${functionName}(${instanceName}->value, ${macroName}(${finalArguments.join(
                                ", ",
                            )}));\n`,
                        );
                        this.write(
                            `if(status != ${error.successValue}) {\n`,
                            () => {
                                this.write(
                                    `Nan::ThrowError(Nan::New("${macroName} failed with error code " + std::string(${error.toStringFunction}(status))).ToLocalChecked());\n`,
                                );
                                this.write("return;\n");
                            },
                            "}\n",
                        );
                        this.write(`info.GetReturnValue().Set(info.This());\n`);
                    },
                    "}\n",
                );
            }
            this.write(
                `void ${className}::${getSettersAndSettersMemberName}(v8::Local<v8::FunctionTemplate> tpl) {\n`,
                () => {
                    for (const [, { memberName }] of this.#gettersAndSetters) {
                        this.write(
                            `Nan::SetPrototypeMethod(tpl, "${lowerFirst(
                                memberName,
                            )}", ${memberName});\n`,
                        );
                    }
                },
                "}\n",
            );
            this.#files.set(
                path.resolve(outDir, `${className}.cpp`),
                this.value(),
            );
        }

        for (const [outFile, contents] of this.#files) {
            await fs.promises.writeFile(outFile, contents);
        }
    }
    #processNode(node: PreprocessorNode) {
        switch (node.type) {
            case PreprocessorNodeType.IfNotDefinedDirective:
            case PreprocessorNodeType.IfDefinedDirective:
            case PreprocessorNodeType.IfDirective:
                for (const child of node.body) {
                    this.#processNode(child);
                }
                break;
            case PreprocessorNodeType.DefineMacroDirective:
                const name = new TextDecoder().decode(node.name.value);
                const hasConstantPrefix =
                    name.startsWith("OPUS_") || name.startsWith("OPE_");
                if (!hasConstantPrefix) {
                    break;
                }
                const hasRequestSuffix = name.endsWith("_REQUEST");
                const hasGetterOrSetterPrefix =
                    name.startsWith("OPUS_GET") || name.startsWith("OPUS_SET");
                /**
                 * ignore OPUS_PROJECTION_, which is for internal-use only and not part of the public API
                 */
                if (hasRequestSuffix && hasGetterOrSetterPrefix) {
                    this.#createOpusRequestGetterOrSetter(node);
                } else if (hasGetterOrSetterPrefix) {
                    this.#macroNodeByName.set(name, node);
                } else if (hasConstantPrefix) {
                    this.#defineNodes.set(name, node);
                }
        }
    }
    async #generateConstantsFiles() {
        this.#generateConstantsHeaderFile();
        this.#generateConstantsSourceFile();
        this.#generateTypeScriptDefinitionConstantsFile();
    }
    async #generateTypeScriptDefinitionConstantsFile() {
        this.write(
            "export interface IConstants {\n",
            () => {
                for (const item of this.#constantGroups.values()) {
                    for (const { name, value } of item.values) {
                        this.write(`${name}: ${value};\n`);
                    }
                }
            },
            "}\n",
        );
        this.#files.set(
            path.resolve(__dirname, "../constants.d.ts"),
            this.value(),
        );
    }
    async #generateConstantsSourceFile() {
        const nativeType = this.#constantValueNativeType;
        const groups = Array.from(this.#constantGroups.values());

        this.write('#include "Constants.h"\n\n');

        this.write("#include <opusenc.h>\n\n");

        for (const group of groups) {
            this.write(
                `static void ${group.setConstantsMethodName}(v8::Local<v8::Object> constants) {\n`,
                () => {
                    for (const { name, value } of group.values) {
                        this.write(
                            `Nan::Set(constants, Nan::New("${name}").ToLocalChecked(), Nan::New(${value}));\n`,
                        );
                    }
                },
                "}\n",
            );
            if (group !== groups[groups.length - 1]) {
                this.append("\n");
            }
        }

        this.write(
            "void Constants::Init(v8::Local<v8::Object> exports) {\n",
            () => {
                this.write(
                    `v8::Local<v8::Object> constants = Nan::New<v8::Object>();\n`,
                );
                for (const group of groups) {
                    this.write(`${group.setConstantsMethodName}(constants);\n`);
                }
                this.write(
                    `Nan::Set(exports, Nan::New("constants").ToLocalChecked(), constants);\n`,
                );
            },
            "}\n",
        );

        for (const group of groups) {
            if (group === groups[0]) {
                this.append("\n");
            }
            this.write(
                `bool ${group.className}::Encode(const ${nativeType}& value, v8::Local<v8::Value>& out) {\n`,
                () => {
                    for (const { name, value } of group.values) {
                        this.write(
                            `if(value == ${name}) {\n`,
                            () => {
                                this.write(`out = Nan::New(${value});\n`);
                                this.write("return true;\n");
                            },
                            "}\n",
                        );
                    }
                    this.write(
                        `Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of ${group.values
                            .map((v) => v.name)
                            .join(", ")}").ToLocalChecked());\n`,
                    );
                    this.write("return false;\n");
                },
                "}\n\n",
            );
            this.write(
                `bool ${group.className}::Convert(const v8::Local<v8::Value>& uncheckedValue, ${nativeType}& out) {\n`,
                () => {
                    this.write(
                        "if(!uncheckedValue->IsInt32()) {\n",
                        () => {
                            this.write(
                                'Nan::ThrowTypeError("value must be an unsigned integer");\n',
                            );
                            this.write("return false;\n");
                        },
                        "}\n",
                    );
                    this.write(
                        "const auto value = Nan::To<v8::Int32>(uncheckedValue).ToLocalChecked()->Value();\n",
                    );
                    for (const { name, value } of group.values) {
                        this.write(
                            `if(value == ${value}) {\n`,
                            () => {
                                this.write(`out = ${name};\n`);
                                this.write("return true;\n");
                            },
                            "}\n",
                        );
                    }
                    this.write(
                        `Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of ${group.values
                            .map((v) => v.name)
                            .join(", ")}").ToLocalChecked());\n`,
                    );
                    this.write("return false;\n");
                },
                "}\n",
            );
            if (group !== groups[groups.length - 1]) {
                this.append("\n");
            }
        }

        this.#files.set(
            path.resolve(__dirname, "../src/Constants.cpp"),
            this.value(),
        );
    }
    /**
     * Set constant groups from define nodes
     */
    #createConstantGroups() {
        const constantGroups = this.#constantGroups;

        /**
         * clean up the define nodes
         */
        for (const [name, node] of this.#defineNodes) {
            if (name.endsWith("_REQUEST")) {
                const getterOrSetterName = name.replace(/_REQUEST$/, "");
                this.#defineNodes.delete(getterOrSetterName);
                this.#defineNodes.delete(name);
                continue;
            } else if (node.value === null) {
                this.#defineNodes.delete(name);
                continue;
            }
        }

        for (const [name] of this.#defineNodes) {
            const slices = name.split("_");
            const prefix = slices[0];
            if (prefix !== "OPUS" && prefix !== "OPE") {
                throw new Exception(`Invalid constant name: ${name}`);
            }
            /**
             * constant group name
             */
            const suffix = slices[1] ?? null;
            if (suffix === null) {
                throw new Exception(`Invalid constant name: ${name}`);
            }
            if (!this.#allowedConstantSuffixes.includes(suffix)) {
                continue;
            }
            let group = constantGroups.get(suffix);
            if (!group) {
                const className = `${capitalize(prefix)}${capitalize(
                    suffix,
                )}Constants`;
                group = {
                    prefix,
                    suffix,
                    setConstantsMethodName: `Set${className}Constants`,
                    className,
                    currentValue: 1,
                    values: [],
                };
                constantGroups.set(suffix, group);
            }
            group.values.push({
                value: group.currentValue++,
                name,
            });
        }
    }
    async #generateConstantsHeaderFile() {
        this.write("#ifndef NATIVE_BINDINGS_OPUS_CONSTANTS_H_\n");
        this.write("#define NATIVE_BINDINGS_OPUS_CONSTANTS_H_\n\n");

        this.write("#include <nan.h>\n\n");

        const nativeType = this.#constantValueNativeType;

        this.write(`class Constants {\n`);
        this.write("public:\n");
        this.indentBlock(() => {
            this.write(`static void Init(v8::Local<v8::Object> exports);\n`);
        });
        this.write("};\n");

        for (const [, group] of this.#constantGroups) {
            this.write(`class ${group.className} {\n`);
            this.write("public:\n");
            this.indentBlock(() => {
                this.write(
                    `// Convert the original constant to a v8::Local<v8::Value>\n`,
                );
                this.write(
                    `static bool Encode(const ${nativeType}& value, v8::Local<v8::Value>&);\n`,
                );
                this.write(
                    `static bool Convert(const v8::Local<v8::Value>&, ${nativeType}& value);\n`,
                );
            });
            this.write("};\n");
        }

        this.write("#endif // NATIVE_BINDINGS_OPUS_CONSTANTS_H_\n");

        this.#files.set(
            path.resolve(__dirname, "../src/Constants.h"),
            this.value(),
        );
    }
    #createOpusRequestGetterOrSetter(node: INodeDefineMacroDirective) {
        const name = this.#textDecoder.decode(node.name.value).split("_");

        let offset = 0;
        // skip the OPE or OPUS prefix
        name[offset++];

        const getterOrSetter = name[offset++];

        if (
            typeof getterOrSetter === "undefined" ||
            (getterOrSetter !== "GET" && getterOrSetter !== "SET")
        ) {
            throw new Exception(`Invalid getter or setter: ${name.join("_")}`);
        }

        if (node.arguments.length !== 0) {
            throw new Exception(
                `Invalid number of arguments for ${name.join("_")}`,
            );
        }

        const optionName = name.slice(1, name.length - 1);

        if (this.#privateOpusOptions.includes(optionName.slice(1).join("_"))) {
            return;
        }

        const memberName = optionName
            .map((part) =>
                Array.from(part)
                    .map((letter, index) =>
                        index === 0
                            ? letter.toUpperCase()
                            : letter.toLowerCase(),
                    )
                    .join(""),
            )
            .join("");

        this.#gettersAndSetters.set(node, {
            type: getterOrSetter,
            memberName: memberName,
            macroName: name.slice(0, name.length - 1).join("_"),
        });
    }
}
