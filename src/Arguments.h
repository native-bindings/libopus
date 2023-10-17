#ifndef OPUSENC_ARGUMENTS_H
#define OPUSENC_ARGUMENTS_H

#include <nan.h>

struct Arguments {
    using IndexIntType = int;
    template<typename T> static bool Unwrap(v8::Local<v8::Value> value, T*& out, std::string argumentName = ""){
        out = Nan::ObjectWrap::Unwrap<T>(Nan::To<v8::Object>(value).ToLocalChecked());
        if(!out) {
            Nan::ThrowError(Nan::New(
                argumentName.empty() ?
                    "Failed to unwrap: " + std::string(typeid(T).name()) :
                    "Failed to unwrap " + std::string(typeid(T).name()) + " from argument " + argumentName
            ).ToLocalChecked());
            return false;
        }
        return true;
    }
    template<typename T> static bool Unwrap(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, T*& out){
        return Unwrap<T>(info[i], out);
    }
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, v8::Local<v8::Function>& out, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int32_t&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int64_t&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::uint32_t&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::string&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int16_t*&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int16_t*&, size_t& len, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::uint8_t*&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::uint8_t*&, size_t& len, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, bool&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, float*&, bool shouldThrowError = true);
    static bool ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, float*&, size_t& len, bool shouldThrowError = true);
};

#endif //OPUSENC_ARGUMENTS_H
