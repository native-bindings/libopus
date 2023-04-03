#ifndef OPUSENC_ARGUMENTS_H
#define OPUSENC_ARGUMENTS_H

#include <nan.h>

struct Arguments {
    template<typename T> static bool Unwrap(v8::Local<v8::Value> value,T*& out){
        out = Nan::ObjectWrap::Unwrap<T>(Nan::To<v8::Object>(value).ToLocalChecked());
        if(!out) {
            out = nullptr;
            return false;
        }
        return true;

    }
    template<typename T> static T* Unwrap(v8::Local<v8::Value> value){
        T* out = Nan::ObjectWrap::Unwrap<T>(Nan::To<v8::Object>(value).ToLocalChecked());
        if(!out) {
            throw std::runtime_error("failed to unwrap C object from JS value");
        }
        return out;
    }
    static bool ConvertValue(v8::Local<v8::Value> value, std::int32_t&);
    static bool ConvertValue(v8::Local<v8::Value> value, std::uint32_t&);
    static bool ConvertValue(v8::Local<v8::Value> value, std::string&);
    static bool ConvertValue(v8::Local<v8::Value> value, std::int16_t*&);
    static bool ConvertValue(v8::Local<v8::Value> value, std::uint8_t*&);
    static bool ConvertValue(v8::Local<v8::Value> value, bool&);
    static bool ConvertValue(v8::Local<v8::Value> value, float*&);
};


#endif //OPUSENC_ARGUMENTS_H
