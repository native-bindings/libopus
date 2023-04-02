import assert from "assert";
import fs from "fs";
import path from "path";
import CodeStream from "codestreamjs";

const startNumberRegularExpression = /^(\-|[0-9]){1}/;

type Value = IValueLiteralNumber | IValueLiteralString;

interface IValueLiteralNumber {
    type: "literalNumber";
    isNegative: boolean;
    value: string;
}

interface IValueLiteralString {
    type: "literalString";
    value: string;
}

type MacroDefinition =
    | {
          type: "valueMacro";
          key: string;
          value: Value | null;
      }
    | {
          type: "functionMacro";
          key: string;
          args: string[];
          contents: string;
      };

class MacrosReader {
    #index = 0;
    readonly #line;
    public constructor(line: string) {
        this.#line = line;
    }
    public read(): MacroDefinition {
        this.#expect("#");
        assert.strict.ok(this.#readIdentifier() === "define");
        this.#readWhiteSpaces();
        const key = this.#readIdentifier();
        this.#readWhiteSpaces();
        if (this.#match("(")) {
            const args = new Array<string>();
            if (!this.#match(")")) {
                do {
                    args.push(this.#readIdentifier());
                } while (!this.#eof() && !this.#match(")") && this.#match(","));
            }
            this.#readWhiteSpaces();
            const contents = this.#remaining();
            this.#match(contents);
            return {
                type: "functionMacro",
                key,
                args,
                contents,
            };
        }
        return {
            type: "valueMacro",
            key,
            value: this.#readValue(),
        };
    }
    #readValue(): Value | null {
        if (this.#remaining().startsWith('"')) {
            return this.#readLiteralString();
        }
        if (startNumberRegularExpression.test(this.#remaining())) {
            return this.#readLiteralNumber();
        }
        return null;
    }
    #readLiteralNumber(): IValueLiteralNumber {
        const isNegative = this.#match("-");
        const startIndex = this.#index;
        while (
            !this.#eof() &&
            startNumberRegularExpression.test(this.#remaining())
        ) {
            this.#advance();
        }
        assert.strict.ok(startIndex !== this.#index);
        return {
            type: "literalNumber",
            isNegative,
            value: this.#line.substring(startIndex, this.#index),
        };
    }
    #readLiteralString(): IValueLiteralString {
        assert.strict.ok(this.#expect('"'));
        const valueStartIndex = this.#index;
        while (!this.#eof() && !this.#match('"')) {
            this.#advance();
        }
        assert.strict.ok(this.#expect('"'));
        return {
            type: "literalString",
            value: this.#line.substring(valueStartIndex, this.#index),
        };
    }
    /**
     * @deprecated just create a damn C or C++ parser written in TypeScript
     */
    #readWhiteSpaces() {
        while (this.#remaining().startsWith(" ")) this.#advance();
    }
    #match(value: string) {
        if (this.#remaining().startsWith(value)) {
            this.#index += value.length;
            return true;
        }
        return false;
    }
    #eof() {
        return this.#index === this.#line.length;
    }
    #remaining() {
        assert.strict.ok(!this.#eof());
        return this.#line.substring(this.#index);
    }
    #advance() {
        assert.strict.ok(!this.#eof());
        this.#index++;
    }
    #expect(value: string) {
        assert.strict.ok(this.#remaining().startsWith(value));
        this.#index += value.length;
    }
    #readIdentifier() {
        const startIndex = this.#index;
        while (!this.#eof() && /^[a-zA-Z0-9_]{1}/.test(this.#remaining())) {
            this.#advance();
        }
        assert.strict.ok(
            startIndex !== this.#index,
            "failed to read identifier"
        );
        return this.#line.substring(startIndex, this.#index);
    }
}

function camelCase(key: string) {
    return key
        .toLowerCase()
        .replace(
            /([a-z])(_)([a-z])/g,
            (_0, a, _1, b) => `${a.toLowerCase()}${b.toUpperCase()}`
        );
}

function upperFirst(key: string) {
    return `${key[0]?.toUpperCase()}${key.substring(1)}`;
}

async function createOpusGettersAndSetters() {
    const files = [
        path.resolve(__dirname, "../opus/include/opus_defines.h"),
        path.resolve(__dirname, "../libopusenc-cmake/src/include/opusenc.h"),
    ];
    const macros = new Set<
        MacroDefinition & {
            uuid: number;
        }
    >();
    for (const f of files) {
        const contents = await fs.promises.readFile(f, "utf8");
        const lines = contents.split("\n");
        let nextUuid = 0;
        for (const l of lines.map((l) => l.trim())) {
            try {
                macros.add({
                    ...new MacrosReader(l).read(),
                    uuid: nextUuid++,
                });
            } catch (reason) {}
        }
    }
    const cs = new CodeStream();
    cs.write('#include "Arguments.h"\n');
    cs.write('#include "Encoder.h"\n');
    cs.write("#include <iostream>\n");
    const setterEnums = [
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
                "OPUS_SET_BANDWIDTH_REQUEST",
                "OPUS_SET_COMPLEXITY_REQUEST",
                "OPUS_SET_INBAND_FEC_REQUEST",
                "OPUS_SET_PACKET_LOSS_PERC_REQUEST",
                "OPUS_SET_DTX_REQUEST",
                "OPUS_SET_VBR_CONSTRAINT_REQUEST",
                "OPUS_SET_FORCE_CHANNELS_REQUEST",
                "OPUS_SET_SIGNAL_REQUEST",
                "OPUS_SET_LSB_DEPTH_REQUEST",
                "OPUS_SET_PREDICTION_DISABLED_REQUEST",
                "OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST",
            ],
        },
    ];
    const getterEnums = [
        {
            args: [
                {
                    type: "opus_int32",
                },
            ],
            matches: [
                "OPUS_GET_APPLICATION_REQUEST",
                "OPUS_GET_BITRATE_REQUEST",
                "OPUS_GET_MAX_BANDWIDTH_REQUEST",
                "OPUS_GET_VBR_REQUEST",
                "OPUS_GET_BANDWIDTH_REQUEST",
                "OPUS_GET_COMPLEXITY_REQUEST",
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
    let argId = 0;
    const getterNames = new Array<string>();
    for (const macro of macros) {
        if (macro.type !== "valueMacro") {
            continue;
        }
        if (!macro.key.endsWith("_REQUEST")) {
            continue;
        }
        const gettersAndSetters = [
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
        ] as const;
        for (const getterOrSetter of gettersAndSetters) {
            if (!macro.key.startsWith(getterOrSetter.keyPrefix)) {
                continue;
            }
            const key = upperFirst(
                camelCase(
                    macro.key.substring(
                        getterOrSetter.keyPrefix.length,
                        macro.key.length - "_REQUEST".length
                    )
                )
            );
            const foundEnum = getterOrSetter.enums.find((e) =>
                e.matches.includes(macro.key)
            );
            if (!foundEnum) {
                continue;
            }
            getterNames.push(`${getterOrSetter.outPrefix}${key}`);
            cs.write(
                `static NAN_METHOD(${getterOrSetter.outPrefix}${key}) {\n`,
                () => {
                    cs.write(
                        `auto* encoder = Arguments::Unwrap<Encoder>(info.This());\n`
                    );

                    const varNames = new Array<string>();
                    if (getterOrSetter.type === "setter") {
                        for (let i = 0; i < foundEnum.args.length; i++) {
                            const varName = `v${argId++}`;
                            cs.write(
                                `${foundEnum.args[i]?.type} ${varName};\n`
                            );
                            cs.write(
                                `if(!Arguments::ConvertValue(info[${i}],${varName})) {\n`,
                                () => {
                                    cs.write(
                                        'Nan::ThrowError("Missing argument");\n'
                                    );
                                    cs.write("return;\n");
                                },
                                "}\n"
                            );
                            varNames.push(varName);
                        }
                    } else {
                        for (let i = 0; i < foundEnum.args.length; i++) {
                            const varName = `v${argId++}`;
                            varNames.push(varName);
                            cs.write(
                                `${foundEnum.args[i]?.type} ${varName};\n`
                            );
                        }
                    }
                    const ctlArguments =
                        getterOrSetter.type === "getter"
                            ? varNames.map((v) => `&${v}`).join(",")
                            : varNames;
                    const macroFunctionName = macro.key.replace(
                        /_REQUEST$/,
                        ""
                    );
                    cs.write(
                        `encoder->error = ope_encoder_ctl(encoder->value,${macroFunctionName}(${ctlArguments}));\n`
                    );
                    cs.write(
                        `if(encoder->error != OPE_OK) {\n`,
                        () => {
                            const errorMessage = `Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked()`;
                            cs.write(`Nan::ThrowError(${errorMessage});\n`);
                            cs.write("return;\n");
                        },
                        "}\n"
                    );
                    if (
                        getterOrSetter.type === "getter" &&
                        varNames.length === 1
                    ) {
                        cs.write(
                            `info.GetReturnValue().Set(Nan::New(${varNames[0]}));\n`
                        );
                    }
                },
                "}\n"
            );
            // cs.write(
            //     `NAN_METHOD(${getterOrSetter.outPrefix}${key}) {\n`,
            //     () => {
            //         cs.write(
            //             "auto* enc = Arguments::Unwrap<Encoder>(info[0]);\n"
            //         );
            //         // cs.write(`ope_encoder_ctl(enc->encoder,${key},);\n`)
            //         // for(const )
            //         const functionMacro = Array.from(macros).find(
            //             (m) =>
            //                 m.key ===
            //                 macro.key.substring(
            //                     0,
            //                     macro.key.length - "_REQUEST".length
            //                 )
            //         );
            //         assert.strict.ok(functionMacro?.type === "functionMacro");
            //         const foundEnum = getterOrSetter.enums?.find((e) =>
            //             e.matches.includes(macro.key)
            //         );
            //         if (foundEnum) {
            //             for (let i = 0; i < foundEnum.args.length; i++) {
            //                 const a = foundEnum.args[i];
            //                 const varName = `v${argId++}`;
            //                 assert.strict.ok(a);
            //                 cs.write(`${a.type} ${varName};\n`);
            //                 cs.write(
            //                     `if(!Arguments::ConvertValue(info[${i}], ${varName})) {\n`,
            //                     () => {
            //                         cs.write(
            //                             `Nan::ThrowError("Failed to get argument");\n`
            //                         );
            //                         cs.write("return;\n");
            //                     },
            //                     "}\n"
            //                 );
            //                 cs.write(
            //                     `auto request = Nan::New<v8::Object>();\n`
            //                 );
            //                 cs.write(
            //                     `Nan::Set(request,Nan::New("type").ToLocalChecked(),Nan::New("${macro.key}").ToLocalChecked());\n`
            //                 );
            //                 cs.write(`auto args = Nan::New<v8::Array>();\n`);
            //                 for (let i = 0; i < foundEnum.args.length; i++) {
            //                     cs.write(
            //                         `Nan::Set(args,Nan::New(${i}),Nan::New(${varName}));\n`
            //                     );
            //                 }
            //                 cs.write(
            //                     'Nan::Set(request,Nan::New("args").ToLocalChecked(),args);\n'
            //                 );
            //                 cs.write("info.GetReturnValue().Set(request);\n");
            //             }
            //         }
            //     },
            //     "}\n"
            // );
        }
    }
    function lowerFirst(value: string) {
        return `${value[0]?.toLowerCase()}${value.substring(1)}`;
    }
    cs.write(
        "void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate>& tpl){\n",
        () => {
            for (const name of getterNames) {
                cs.write(
                    `Nan::SetPrototypeMethod(tpl,"${lowerFirst(
                        name
                    )}",${name});\n`
                );
            }
        },
        "}\n"
    );
    cs.write(
        "void SetConstants(v8::Local<v8::Object> exports){\n",
        () => {
            cs.write("auto constants = Nan::New<v8::Object>();\n");
            for (const m of macros) {
                if (m.type !== "valueMacro") {
                    continue;
                }
                cs.write(
                    `Nan::Set(constants,Nan::New("${m.key}").ToLocalChecked(),Nan::New(${m.uuid}));\n`
                );
            }
            cs.write(
                'Nan::Set(exports,Nan::New("constants").ToLocalChecked(),constants);\n'
            );
        },
        "}\n"
    );
    await fs.promises.writeFile(
        path.resolve(__dirname, "../Constants.cpp"),
        cs.value()
    );
}

(async () => {
    await createOpusGettersAndSetters();
})();
