#include "Arguments.h"

bool AssertType(
    Nan::NAN_METHOD_ARGS_TYPE info,
    Arguments::IndexIntType i,
    const char* name,
    bool shouldThrowError,
    bool checkType(v8::Local<v8::Value>)
){
    if(checkType(info[i])){
        return true;
    }
    if(shouldThrowError){
        Nan::ThrowError(Nan::New("Argument " + std::to_string(i + 1) + " must be a " + name).ToLocalChecked());
    }
    return false;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int32_t& out, bool shouldThrowError){
    if(!AssertType(info,i,"valid signed 32-bit integer",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsInt32();
    })){
        return false;
    }
    out = Nan::To<v8::Int32>(info[i]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, v8::Local<v8::Function>& out, bool shouldThrowError){
    if(!AssertType(info,i,"valid function",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsFunction();
    })){
        return false;
    }
    out = Nan::To<v8::Function>(info[i]).ToLocalChecked();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::uint32_t& out, bool shouldThrowError){
    if(!AssertType(info,i,"valid unsigned 32-bit integer",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsUint32();
    })){
        return false;
    }
    out = Nan::To<v8::Uint32>(info[i]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::string& out, bool shouldThrowError){
    if(!AssertType(info,i,"string",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsString();
    })){
        return false;
    }
    auto value = info[i];
    const auto length = Nan::DecodeBytes(value);
    char buffer[length];
    Nan::DecodeWrite(buffer,length,value);
    out = std::string(buffer,length);
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int16_t*& out, bool shouldThrowError){
    if(!AssertType(info,i,"valid Int16Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsInt16Array();
    })){
        return false;
    }
    out = *Nan::TypedArrayContents<std::int16_t>(info[i]);
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::int16_t*& out, size_t& len, bool shouldThrowError){
    if(!AssertType(info,i,"valid Int16Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsInt16Array();
    })){
        return false;
    }
    auto contents = Nan::TypedArrayContents<std::int16_t>(info[i]);
    out = *contents;
    len = contents.length();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, float *& out, bool shouldThrowError) {
    if(!AssertType(info,i,"valid Float32Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsFloat32Array();
    })){
        return false;
    }
    out = *Nan::TypedArrayContents<float>(info[i]);
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, float*& out, size_t& len, bool shouldThrowError) {
    if(!AssertType(info,i,"valid Float32Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsFloat32Array();
    })){
        return false;
    }
    auto contents = Nan::TypedArrayContents<float>(info[i]);
    out = *contents;
    len = contents.length();
    return true;
}


bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, std::uint8_t *& out, bool shouldThrowError) {
    if(!AssertType(info,i,"valid Uint8Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsUint8Array();
    })){
        return false;
    }
    out = *Nan::TypedArrayContents<std::uint8_t>(info[i]);
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, IndexIntType i, bool & out, bool shouldThrowError) {
    if(!AssertType(info,i,"boolean",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsInt16Array();
    })){
        return false;
    }
    out = Nan::To<v8::Boolean>(info[i]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, Arguments::IndexIntType i, int64_t & out, bool shouldThrowError) {
    if(!AssertType(info,i,"valid signed 64-bit integer",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsNumber();
    })){
        return false;
    }
    out = Nan::To<v8::Number>(info[i]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::ConvertValue(Nan::NAN_METHOD_ARGS_TYPE info, Arguments::IndexIntType i, uint8_t *& out, size_t &len,
                             bool shouldThrowError) {
    if(!AssertType(info,i,"valid Uint8Array instance",shouldThrowError,[](v8::Local<v8::Value> val){
        return val->IsUint8Array();
    })){
        return false;
    }
    auto contents = Nan::TypedArrayContents<std::uint8_t>(info[i]);
    out = *contents;
    len = contents.length();
    return true;
}
