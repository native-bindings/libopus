#include "Arguments.h"

bool Arguments::Convert(int index, std::string& out) const {
    if(!AssertArgumentType(index, IsString, "String")) {
        return false;
    }
    const auto arg = info[index];
    std::vector<char> buf(Nan::DecodeBytes(arg));
    const auto writeResult = Nan::DecodeWrite(buf.data(), buf.size(), arg);
    if(writeResult <= 0) {
        ThrowError("Failed to decode argument " + std::to_string(index + 1) + ": " + std::to_string(writeResult));
        return false;
    }
    if(static_cast<size_t>(writeResult) != buf.size()) {
        ThrowError("Failed to decode argument " + std::to_string(index + 1) + ".");
        return false;
    }
    out = std::string(buf.data(), buf.size());
    return true;
}

bool Arguments::Convert(int index, uint64_t & out) const {
    std::string value;
    if(!Convert(index, value)) {
        return false;
    }
    out = std::stoul(value, nullptr, 10);
    return true;
}

void Arguments::ThrowError(const std::string&& value) {
    Nan::ThrowError(Nan::New(value).ToLocalChecked());
}

Arguments::Arguments(
    ArgumentsType& info,
    std::string&& name
):
    name(name),
    info(info)
{}

bool Arguments::AssertArgumentIndex(int index) const {
    if(HasArgument(index)) {
        return true;
    }
    const auto argumentNumber = std::to_string(index + 1);
    ThrowError("Expected argument number " + argumentNumber + ", but it was not provided.");
    return false;
}

bool Arguments::AssertArgumentType(
    int index,
    const std::function<bool(const v8::Local<v8::Value> &)>& runCheck,
    std::string&& expectedType
) const {
    if(!AssertArgumentIndex(index)) {
        return false;
    }
    const auto arg = info[index];
    if(!runCheck(arg)) {
        ThrowError("Expected argument number " + std::to_string(index + 1) + " to be of type " + expectedType + ".");
        return false;
    }
    return true;
}

bool Arguments::IsString(const v8::Local<v8::Value>& arg) {
    return arg->IsString();
}

bool Arguments::IsNumber(const v8::Local<v8::Value>& arg) {
    return arg->IsNumber();
}

bool Arguments::IsUint32(const v8::Local<v8::Value>& arg) {
    return arg->IsUint32();
}

bool Arguments::Convert(int index, int64_t & out) const {
    std::string value;
    if(!Convert(index, value)) {
        return false;
    }
    out = std::stol(value, nullptr, 10);
    return true;
}

bool Arguments::Convert(int index, int32_t& out) const {
    v8::Local<v8::Value> val;
    if(!GetArgument(index, val) || !AssertArgumentType(index, IsInt32, "Int32")) {
        return false;
    }
    out = Nan::To<v8::Int32>(val).ToLocalChecked()->Value();
    return true;
}

bool Arguments::IsInt32(const v8::Local<v8::Value>& arg) {
    return arg->IsInt32();
}

bool Arguments::Get(const uint32_t& value, v8::Local<v8::Value> &out) {
    out = Nan::New<v8::Uint32>(value);
    return true;
}

bool Arguments::Get(const uint64_t& input, v8::Local<v8::Value>& out) {
    out = Nan::New(std::to_string(input)).ToLocalChecked();
    return true;
}

bool Arguments::Get(const int64_t& value, v8::Local<v8::Value> &out) {
    out = Nan::New(std::to_string(value)).ToLocalChecked();
    return true;
}

bool Arguments::Convert(const int index, bool& out) const {
    if(!AssertArgumentIndex(index)) {
        return false;
    }
    if(!AssertArgumentType(index, Arguments::IsBoolean, "Boolean")) {
        return false;
    }
    out = Nan::To<v8::Boolean>(info[index]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::IsBoolean(const v8::Local<v8::Value>& val) {
    return val->IsBoolean();
}

bool Arguments::Convert(const int index, uint32_t& out) const {
    if(!AssertArgumentType(index, Arguments::IsUint32, "Uint32")) {
        return false;
    }
    out = Nan::To<v8::Uint32>(info[index]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::Convert(const int index, double& out) const {
    if(!AssertArgumentType(index, Arguments::IsNumber, "IsNumber")) {
        return false;
    }
    out = Nan::To<v8::Number>(info[index]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::Convert(const int index, uint16_t& out) const {
    if(!AssertArgumentType(index, Arguments::IsUint32, "Uint32")) {
        return false;
    }
    out = Nan::To<v8::Uint32>(info[index]).ToLocalChecked()->Value();
    return true;
}

bool Arguments::HasArgument(const int index) const {
    return index <= (info.Length() - 1);
}

bool Arguments::Convert(const int index, v8::Local<v8::Function>& out) const {
    if(!AssertArgumentType(index, Arguments::IsFunction, "Function")) {
        return false;
    }
    out = Nan::To<v8::Function>(info[index]).ToLocalChecked();
    return true;
}

bool Arguments::IsFunction(const v8::Local<v8::Value>& val) {
    return val->IsFunction();
}

bool Arguments::IsInt16Array(const v8::Local<v8::Value>& val) {
    return val->IsInt16Array();
}

bool Arguments::IsUint8Array(const v8::Local<v8::Value>& val) {
    return val->IsUint8Array();
}

bool Arguments::GetArgument(const int index, v8::Local<v8::Value> &out) const {
    if(!AssertArgumentIndex(index)) {
        return false;
    }
    out = info[index];
    return true;
}
