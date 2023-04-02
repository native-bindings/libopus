#include "Arguments.h"

bool Arguments::ConvertValue(v8::Local<v8::Value> value, std::int32_t& out){
    if(!value->IsInt32()){
        return false;
    }
    out = Nan::To<v8::Int32>(value).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, std::uint32_t& out){
    if(!value->IsUint32()){
        return false;
    }
    out = Nan::To<v8::Uint32>(value).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, std::string& out){
    if(!value->IsString()){
        return false;
    }
    const auto length = Nan::DecodeBytes(value);
    char buffer[length];
    Nan::DecodeWrite(buffer,length,value);
    out = std::string(buffer,length);
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, std::int16_t*& out){
    out = nullptr;
    if(!value->IsInt16Array()){
        return false;
    }
    v8::Local<v8::Int16Array> view = value.As<v8::Int16Array>();
    v8::Local<v8::ArrayBuffer> arrayBuffer = view->Buffer();
    auto* buffer = reinterpret_cast<std::uint8_t*>(arrayBuffer->Data());
    buffer += view->ByteOffset();
    out = reinterpret_cast<std::int16_t*>(buffer);
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, float *& out) {
    if(!value->IsFloat32Array()){
        return false;
    }
    auto view = value.As<v8::Float32Array>();
    float* buf = reinterpret_cast<float*>(view->Buffer()->Data());
    buf += view->ByteOffset();
    out = buf;
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, std::uint8_t *& out) {
    if(!value->IsFloat32Array()){
        return false;
    }
    auto view = value.As<v8::Float32Array>();
    std::uint8_t* buf = reinterpret_cast<std::uint8_t*>(view->Buffer()->Data());
    buf += view->ByteOffset();
    out = buf;
    return true;
}

bool Arguments::ConvertValue(v8::Local<v8::Value> value, bool & out) {
    if(!value->IsBoolean()) {
        return false;
    }
    out = Nan::To<v8::Boolean>(value).ToLocalChecked()->Value();
    return true;
}
