import fs from "fs";
import path from "path";
import CodeStream from "codestreamjs";
import {
    getMacroFunctionName,
    getNativeMethodNameFromKey,
    lowerFirst,
} from "./helpers";
import MacroReader, { MacroDefinition } from "./MacroReader";
import Exception from "../test/Exception";

interface IEnum {
    args: {
        type: string;
    }[];
    matches: string[];
}

const setterEnums: IEnum[] = [
    {
        args: [
            {
                type: "opus_uint32",
            },
        ],
        matches: ["OPUS_SET_FINAL_RANGE_REQUEST"],
    },
    {
        args: [
            {
                type: "opus_int32",
            },
        ],
        matches: [
            "OPE_SET_DECISION_DELAY_REQUEST",
            "OPE_SET_MUXING_DELAY_REQUEST",
            "OPE_SET_COMMENT_PADDING_REQUEST",
            "OPE_SET_SERIALNO_REQUEST",
            "OPUS_SET_EXPERT_FRAME_DURATION_REQUEST",
            "OPUS_SET_APPLICATION_REQUEST",
            "OPUS_SET_BITRATE_REQUEST",
            "OPUS_SET_MAX_BANDWIDTH_REQUEST",
            "OPUS_SET_VBR_REQUEST",
            "OPUS_SET_IN_DTX_REQUEST",
            "OPUS_SET_BANDWIDTH_REQUEST",
            "OPUS_SET_COMPLEXITY_REQUEST",
            "OPUS_SET_INBAND_FEC_REQUEST",
            "OPUS_SET_PACKET_LOSS_PERC_REQUEST",
            "OPUS_SET_DTX_REQUEST",
            "OPUS_SET_VBR_CONSTRAINT_REQUEST",
            "OPUS_SET_GAIN_REQUEST",
            "OPUS_SET_FORCE_CHANNELS_REQUEST",
            "OPUS_SET_SIGNAL_REQUEST",
            "OPUS_SET_LSB_DEPTH_REQUEST",
            "OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST",
            "OPUS_SET_PREDICTION_DISABLED_REQUEST",
            "OPUS_SET_PITCH_REQUEST",
            "OPUS_SET_EXPERT_FRAME_DURATION_REQUEST",
            "OPUS_SET_SAMPLE_RATE_REQUEST",
            "OPUS_SET_LOOKAHEAD_REQUEST",
            "OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST",
        ],
    },
];

const getterEnums: IEnum[] = [
    {
        args: [
            {
                type: "opus_uint32",
            },
        ],
        matches: ["OPUS_GET_FINAL_RANGE_REQUEST"],
    },
    {
        args: [
            {
                type: "opus_int32",
            },
        ],
        matches: [
            "OPUS_GET_LOOKAHEAD_REQUEST",
            "OPUS_GET_SAMPLE_RATE_REQUEST",
            "OPUS_GET_PITCH_REQUEST",
            "OPUS_GET_GAIN_REQUEST",
            "OPUS_GET_LAST_PACKET_DURATION_REQUEST",
            "OPUS_GET_EXPERT_FRAME_DURATION_REQUEST",
            "OPUS_GET_PHASE_INVERSION_DISABLED_REQUEST",
            "OPUS_GET_APPLICATION_REQUEST",
            "OPUS_GET_BITRATE_REQUEST",
            "OPUS_GET_MAX_BANDWIDTH_REQUEST",
            "OPUS_GET_VBR_REQUEST",
            "OPUS_GET_BANDWIDTH_REQUEST",
            "OPUS_GET_COMPLEXITY_REQUEST",
            "OPUS_GET_IN_DTX_REQUEST",
            "OPUS_GET_INBAND_FEC_REQUEST",
            "OPUS_GET_PACKET_LOSS_PERC_REQUEST",
            "OPUS_GET_DTX_REQUEST",
            "OPUS_GET_VBR_CONSTRAINT_REQUEST",
            "OPUS_GET_FORCE_CHANNELS_REQUEST",
            "OPUS_GET_SIGNAL_REQUEST",
            "OPUS_GET_LSB_DEPTH_REQUEST",
            "OPUS_GET_PREDICTION_DISABLED_REQUEST",
        ],
    },
];

interface IGetterOrSetter {
    type: "getter" | "setter";
    keyPrefix: string;
    outPrefix: string;
    enums: IEnum[];
}

const gettersAndSetters: IGetterOrSetter[] = [
    {
        type: "getter",
        keyPrefix: "OPUS_GET_",
        outPrefix: "Get",
        enums: getterEnums,
    },
    {
        type: "setter",
        enums: setterEnums,
        keyPrefix: "OPUS_SET_",
        outPrefix: "Set",
    },
];

export class ConstantsCodeGenerator extends CodeStream {
    #uuid = 0;
    readonly #allMacros;
    public constructor(
        allMacros: Set<
            MacroDefinition & {
                uuid: number;
            }
        >
    ) {
        super();
        this.#allMacros = allMacros;
    }
    public async generate() {
        await this.#generateOpusGettersAndSettersFile();
        await this.#createConstantsCppFile();
        await this.#generateTypeScriptConstantsFile();
    }
    async #generateOpusGettersAndSettersFile() {
        this.write('#include "Encoder.h"\n');
        this.write('#include "Decoder.h"\n');
        this.write('#include "Arguments.h"\n\n');

        this.write(
            `namespace bindings {\n`,
            () => {
                this.#generateOpusGettersAndSetters({
                    className: "Encoder",
                    ctlFunctionName: "opus_encoder_ctl",
                });
                this.#generateOpusGettersAndSetters({
                    ctlFunctionName: "opus_decoder_ctl",
                    className: "Decoder",
                });
            },
            "}\n"
        );

        await fs.promises.writeFile(
            path.resolve(__dirname, "../src/EncoderGettersAndSetters.cpp"),
            this.value()
        );
    }
    async #createConstantsCppFile() {
        this.write('#include "Arguments.h"\n');
        this.write('#include "opusenc/Encoder.h"\n\n');

        this.write(
            "namespace Constants {\n",
            () => {
                this.write(
                    "void Init(v8::Local<v8::Object> exports){\n",
                    () => {
                        this.write(
                            "auto constants = Nan::New<v8::Object>();\n"
                        );
                        for (const m of this.#allMacros) {
                            if (m.type !== "valueMacro") {
                                continue;
                            }
                            this.write(
                                `Nan::Set(constants,Nan::New("${m.key}").ToLocalChecked(),Nan::New(${m.uuid}));\n`
                            );
                        }
                        this.write(
                            'Nan::Set(exports,Nan::New("constants").ToLocalChecked(),constants);\n'
                        );
                    },
                    "}\n"
                );
            },
            "}\n"
        );
        this.write(
            `namespace bindings::opusenc {\n`,
            () => {
                this.write(
                    "bool ConvertOpusJavaScriptConstant(v8::Local<v8::Value> val, int& out) {\n",
                    () => {
                        this.write(`if(!val->IsNumber()) return false;\n`);
                        this.write(
                            "const auto n = Nan::To<v8::Number>(val).ToLocalChecked()->Value();\n"
                        );
                        for (const m of this.#allMacros) {
                            if (m.type !== "valueMacro") continue;
                            this.write(
                                `if(n == ${m.uuid}) {\n`,
                                () => {
                                    this.write(`out = ${m.key};\n`);
                                    this.write("return true;\n");
                                },
                                "}\n"
                            );
                        }
                        this.write("return false;\n");
                    },
                    "}\n"
                );
            },
            "}\n"
        );
        this.write(
            `namespace bindings {\n`,
            () => {
                this.write(
                    "namespace opusenc {\n",
                    () => {
                        this.#generateOpusEncGettersAndSetters();
                    },
                    "}\n"
                );
                // this.write(
                //     `namespace opus {\n`,
                //     () => {
                //     },
                //     "}\n"
                // );
            },
            "}\n"
        );
        await fs.promises.writeFile(
            path.resolve(__dirname, "../src/Constants.cpp"),
            this.value()
        );
    }
    #generateOpusGettersAndSetters({
        className,
        ctlFunctionName,
    }: {
        ctlFunctionName: string;
        className: string;
    }) {
        interface IMember {
            nativeMethod: string;
            foundEnum: IEnum;
            getterOrSetter: IGetterOrSetter;
            macro: MacroDefinition & {
                uuid: number;
            };
        }
        const members = new Set<IMember>();
        for (const macro of this.#allMacros) {
            if (!macro.key.endsWith("_REQUEST")) {
                continue;
            }
            for (const getterOrSetter of gettersAndSetters) {
                if (!macro.key.startsWith(getterOrSetter.keyPrefix)) {
                    continue;
                }
                const key = getNativeMethodNameFromKey(
                    macro.key,
                    getterOrSetter.keyPrefix
                );
                const foundEnum = getterOrSetter.enums.find((e) =>
                    e.matches.includes(macro.key)
                );
                if (!foundEnum) {
                    throw new Exception(
                        `Found no enum for macro: ${macro.key}`
                    );
                }
                const nativeMethod = `${getterOrSetter.outPrefix}${key}`;
                this.write(`// static NAN_METHOD(${nativeMethod});\n`);
                members.add({
                    macro,
                    getterOrSetter,
                    nativeMethod,
                    foundEnum,
                });
            }
        }
        for (const { macro, foundEnum, getterOrSetter } of members) {
            if (!macro.key.startsWith(getterOrSetter.keyPrefix)) {
                continue;
            }
            const key = getNativeMethodNameFromKey(
                macro.key,
                getterOrSetter.keyPrefix
            );
            /**
             * write the original macro key
             */
            this.write(`// ${macro.key}\n`);
            /**
             * write member implementation
             */
            this.write(
                `NAN_METHOD(${className}::${getterOrSetter.outPrefix}${key}) {\n`,
                () => {
                    this.write(`${className}* codec;\n`);
                    this.write(
                        `if(!Arguments::Unwrap<${className}>(info.This(), codec)) {\n`,
                        () => {
                            this.write("return;\n");
                        },
                        "}\n"
                    );
                    const argNames = foundEnum.args.map((arg, index) => ({
                        type: arg.type,
                        index,
                        name: `v${this.#uuid++}`,
                    }));
                    for (const arg of argNames) {
                        this.write(`${arg.type} ${arg.name};\n`);
                    }
                    {
                        this.write(
                            `if(\n`,
                            () => {
                                for (const arg of argNames) {
                                    this.write(
                                        `!Arguments::ConvertValue(info,${arg.index},${arg.name})`
                                    );
                                    if (arg !== argNames[argNames.length - 1]) {
                                        this.append(" ||");
                                    }
                                    this.append("\n");
                                }
                            },
                            ") {\n"
                        );
                        this.indentBlock(() => {
                            this.write("return;\n");
                        });
                        this.write("}\n");
                    }
                    let ctlArguments: string;
                    if (getterOrSetter.type === "setter") {
                        ctlArguments = argNames
                            .map((arg) => arg.name)
                            .join(", ");
                    } else {
                        ctlArguments = argNames
                            .map((arg) => `&${arg.name}`)
                            .join(",");
                    }
                    this.write(
                        `codec->error = ${ctlFunctionName}(codec->value,${getMacroFunctionName(
                            macro.key
                        )}(${ctlArguments}));\n`
                    );
                    this.write(
                        `if(codec->error != OPUS_OK) {\n`,
                        () => {
                            const errorMessage = `Nan::New("Failed to call ${ctlFunctionName} with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked()`;
                            this.write(`Nan::ThrowError(${errorMessage});\n`);
                            this.write("return;\n");
                        },
                        "}\n"
                    );
                    const [firstArg] = argNames;
                    if (argNames.length > 1 || !firstArg) {
                        throw new Exception(
                            `We do not support getter or setter with more than 1 argument`
                        );
                    }
                    this.write(
                        `info.GetReturnValue().Set(Nan::New(${firstArg.name}));\n`
                    );
                },
                "}\n"
            );
        }
        for (const m of members) {
            this.write(`// ${lowerFirst(m.nativeMethod)}(`);
            if (m.getterOrSetter.type === "setter") {
                this.append("value: number");
            }
            this.append("): ");
            if (m.getterOrSetter.type === "setter") {
                this.append("void");
            } else {
                this.append("number");
            }
            this.append(";\n");
        }
        this.write(
            `void ${className}::SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl) {\n`,
            () => {
                for (const m of members) {
                    this.write(
                        `Nan::SetPrototypeMethod(tpl,"${lowerFirst(
                            m.nativeMethod
                        )}",${m.nativeMethod});\n`
                    );
                }
            },
            "}\n"
        );
    }
    #generateOpusEncGettersAndSetters() {
        const getterNames = new Array<string>();
        for (const macro of this.#allMacros) {
            if (macro.type !== "valueMacro") {
                continue;
            }
            if (!macro.key.endsWith("_REQUEST")) {
                continue;
            }
            for (const getterOrSetter of gettersAndSetters) {
                if (!macro.key.startsWith(getterOrSetter.keyPrefix)) {
                    continue;
                }
                const key = getNativeMethodNameFromKey(
                    macro.key,
                    getterOrSetter.keyPrefix
                );
                const foundEnum = getterOrSetter.enums.find((e) =>
                    e.matches.includes(macro.key)
                );
                if (!foundEnum) {
                    continue;
                }
                getterNames.push(`${getterOrSetter.outPrefix}${key}`);
                this.write(
                    `static NAN_METHOD(${getterOrSetter.outPrefix}${key}) {\n`,
                    () => {
                        this.write(`Encoder* encoder;\n`);
                        this.write(
                            `if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {\n`,
                            () => {
                                this.write("return;\n");
                            },
                            "}\n"
                        );

                        const varNames = new Array<string>();
                        if (getterOrSetter.type === "setter") {
                            for (let i = 0; i < foundEnum.args.length; i++) {
                                const varName = `v${this.#uuid++}`;
                                this.write(
                                    `${foundEnum.args[i]?.type} ${varName};\n`
                                );
                                this.write(
                                    `if(!Arguments::ConvertValue(info,${i},${varName})) {\n`,
                                    () => {
                                        this.write("return;\n");
                                    },
                                    "}\n"
                                );
                                varNames.push(varName);
                            }
                        } else {
                            for (let i = 0; i < foundEnum.args.length; i++) {
                                const varName = `v${this.#uuid++}`;
                                varNames.push(varName);
                                this.write(
                                    `${foundEnum.args[i]?.type} ${varName};\n`
                                );
                            }
                        }
                        const ctlArguments =
                            getterOrSetter.type === "getter"
                                ? varNames.map((v) => `&${v}`).join(",")
                                : varNames;
                        const macroFunctionName = getMacroFunctionName(
                            macro.key
                        );
                        this.write(
                            `encoder->error = ope_encoder_ctl(encoder->value,${macroFunctionName}(${ctlArguments}));\n`
                        );
                        this.write(
                            `if(encoder->error != OPE_OK) {\n`,
                            () => {
                                const errorMessage = `Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked()`;
                                this.write(
                                    `Nan::ThrowError(${errorMessage});\n`
                                );
                                this.write("return;\n");
                            },
                            "}\n"
                        );
                        if (
                            getterOrSetter.type === "getter" &&
                            varNames.length === 1
                        ) {
                            this.write(
                                `info.GetReturnValue().Set(Nan::New(${varNames[0]}));\n`
                            );
                        }
                    },
                    "}\n"
                );
            }
        }
        this.write(
            "void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl){\n",
            () => {
                for (const name of getterNames) {
                    this.write(
                        `Nan::SetPrototypeMethod(tpl,"${lowerFirst(
                            name
                        )}",${name});\n`
                    );
                }
            },
            "}\n"
        );
    }
    async #generateTypeScriptConstantsFile() {
        this.write(
            "const constants: {\n",
            () => {
                for (const m of this.#allMacros) {
                    if (m.type !== "valueMacro") {
                        continue;
                    }
                    this.write(`${m.key}: ${m.uuid};\n`);
                }
            },
            "};\n"
        );
        this.write("export default constants;\n");
        await fs.promises.writeFile(
            path.resolve(__dirname, "../constants.d.ts"),
            this.value()
        );
    }
}

(async () => {
    let nextUuid = 0;
    const macros = new Set<
        MacroDefinition & {
            uuid: number;
        }
    >();
    for (const f of [
        path.resolve(__dirname, "../opus/include/opus_defines.h"),
        path.resolve(__dirname, "../libopusenc-cmake/src/include/opusenc.h"),
    ]) {
        const contents = await fs.promises.readFile(f, "utf8");
        const lines = contents.split("\n");
        for (const l of lines.map((l) => l.trim())) {
            try {
                macros.add({
                    ...new MacroReader(l).read(),
                    uuid: nextUuid++,
                });
            } catch (reason) {}
        }
    }
    await new ConstantsCodeGenerator(macros).generate();
})().catch((reason) => {
    if (reason instanceof Exception) {
        console.error(reason.what());
    } else {
        console.error(reason);
    }
    process.exitCode = 1;
});
