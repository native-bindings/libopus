#include "Encoder.h"
#include "core/Arguments.h"
#include "../Constants.h"

using namespace bindings::opusenc;

Nan::Persistent<v8::Function> Encoder::constructor;

static bool ValidateFamily(int family) {
    if(family != 0 && family != 1) {
        Nan::ThrowError(Nan::New(std::string("Expected family argument to be 0 for mono or 1 for stereo, but got " ) + std::to_string(family) + " instead").ToLocalChecked());
        return false;
    }
    return true;
}

static bool AssertNotCreatedEncoder(Encoder* enc){
    if(enc->value){
        Nan::ThrowError("Encoder was already created previously");
        return false;
    }
    return true;
}

bool Encoder::HasError(std::string&& prefix) const {
    if(error != OPE_OK){
        Nan::ThrowError(Nan::New(prefix + " with error: " + ope_strerror(error)).ToLocalChecked());
        return true;
    }
    return false;
}

void Encoder::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Encoder").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl,"createFile",CreateFile);
    Nan::SetPrototypeMethod(tpl,"createPull",CreatePull);
    Nan::SetPrototypeMethod(tpl,"drain",Drain);
    Nan::SetPrototypeMethod(tpl,"getPage",GetPage);
    Nan::SetPrototypeMethod(tpl,"write",Write);
    Nan::SetPrototypeMethod(tpl,"flushHeader",FlushHeader);
    Nan::SetPrototypeMethod(tpl,"chainCurrent",ChainCurrent);
    Nan::SetPrototypeMethod(tpl,"writeFloat",WriteFloat);
    Nan::SetPrototypeMethod(tpl,"continueNewFile",ContinueNewFile);
    Nan::SetPrototypeMethod(tpl,"deferredInitWithMapping",DeferredInitWithMapping);
    SetGettersAndSettersPrototypeMethods(tpl);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(exports,Nan::New("Encoder").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Encoder::New) {
    auto* encoder = new Encoder();
    encoder->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Encoder::CreatePull){
    Encoder* enc;
    Comments* comments;
    int rate,channels,family;
    Arguments args(info, "createPull");
    if(
        !args.Unwrap(info.This(), enc) ||
        !args.Unwrap(0, comments) ||
        !args.Convert(1, rate) ||
        !args.Convert(2, channels) ||
        !args.Convert(3, family)
    ){
        return;
    }
    if(!AssertNotCreatedEncoder(enc) || !ValidateFamily(family)){
        return;
    }
    enc->value = ope_encoder_create_pull(comments->value, rate, channels, family, &enc->error);
    if(enc->HasError("Failed to create encoder")) {
        return;
    }
}

NAN_METHOD(Encoder::CreateFile){
    Encoder* enc;
    Arguments args(info, "createFile");
    if(!args.Unwrap(enc) || !AssertNotCreatedEncoder(enc)){
        return;
    }
    Comments* comments;
    std::string file;
    int rate,channels,family;
    if(
        !args.Unwrap(0, comments) ||
        !args.Convert(1, file) ||
        !args.Convert(2, rate) ||
        !args.Convert(3, channels) ||
        !args.Convert(4, family)
    ){
        return;
    }
    if(!ValidateFamily(family)){
        return;
    }
    enc->value = ope_encoder_create_file(file.c_str(),comments->value,rate,channels,family,&enc->error);
    if(enc->HasError("Failed to create direct-file encoder")) {
        return;
    }
}

NAN_METHOD(Encoder::Drain){
    Encoder* enc;
    Arguments args(info, "drain");
    if(!args.Unwrap(enc)){
        return;
    }
    enc->error = ope_encoder_drain(enc->value);
    if(enc->HasError("Failed to drain encoder")) {
        return;
    }
}

NAN_METHOD(Encoder::ChainCurrent){
    Encoder* enc;
    Comments* comments;
    Arguments args(info, "chainCurrent");
    if(
        !args.Unwrap(enc) ||
        !args.Unwrap(0, comments)
    ) {
        return;
    }
    enc->error = ope_encoder_chain_current(enc->value,comments->value);
    if(enc->HasError("Failed to chain current")){
        return;
    }
}

NAN_METHOD(Encoder::FlushHeader) {
    Encoder* enc;
    Arguments args(info, "flushHeader");
    if(!args.Unwrap(enc)){
        return;
    }
    enc->error = ope_encoder_flush_header(enc->value);
    if(enc->HasError("Failed to flush header")) {
        return;
    }
}

NAN_METHOD(Encoder::Write){
    Encoder* enc;
    TypedArrayContents<std::int16_t> pcm;
    int samplesPerChannel;
    Arguments args(info, "write");
    if(
        !args.Unwrap(enc) ||
        !args.ConvertTypedArrayContents(0, pcm) ||
        !args.Convert(1, samplesPerChannel)
    ){
        return;
    }
    enc->error = ope_encoder_write(enc->value, pcm.value, samplesPerChannel);
    if(enc->HasError("Failed to write to encoder")){
        return;
    }
}

NAN_METHOD(Encoder::DeferredInitWithMapping) {
    Encoder* enc;
    int family, streams,coupled_streams;
    TypedArrayContents<std::uint8_t> mapping;
    Arguments args(info, "deferredInitWithMapping");
    if(
        !args.Unwrap(enc) ||
        !args.Convert(0, family) ||
        !args.Convert(1, streams) ||
        !args.Convert(2, coupled_streams) ||
        !args.ConvertTypedArrayContents(3, mapping)
    ){
        return;
    }
    enc->error = ope_encoder_deferred_init_with_mapping(enc->value,family,streams,coupled_streams,mapping.value);
    if(enc->HasError("ope_encoder_deferred_init_with_mapping call failed")) {
        return;
    }
}

NAN_METHOD(Encoder::ContinueNewFile){
    Encoder* enc;
    Comments* comments;
    std::string path;
    Arguments args(info, "continueNewFile");
    if(
        !args.Unwrap(enc) ||
        !args.Convert(0, path) ||
        !args.Unwrap(1, comments)
    ){
        return;
    }
    enc->error = ope_encoder_continue_new_file(enc->value, path.c_str(), comments->value);
    if(enc->HasError("Failed to continue with new file")) {
        return;
    }
}

NAN_METHOD(Encoder::GetPage) {
    Encoder* enc;
    bool flush;
    opus_int32 len;
    unsigned char* page;
    Arguments args(info, "getPage");

    if(!args.Unwrap(enc)) {
        return;
    }

    if(!args.ConvertOptional(0, flush)){
        flush = false;
    }

    const auto hasPage = ope_encoder_get_page(enc->value, &page, &len, flush ? 1 : 0);

    if(hasPage == 1) {
        char copy[len];
        memcpy(copy, page, len);
        info.GetReturnValue().Set(Nan::CopyBuffer(copy, len).ToLocalChecked());
    } else if(hasPage == 0) {
        info.GetReturnValue().Set(Nan::Null());
    }
}

NAN_METHOD(Encoder::WriteFloat){
    Encoder* enc;
    TypedArrayContents<float> pcm;
    int samplesPerChannel;
    Arguments args(info, "writeFloat");
    if(
        !args.Unwrap(enc) ||
        !args.ConvertTypedArrayContents(0, pcm) ||
        !args.Convert(1, samplesPerChannel)
    ) {
        return;
    }
    enc->error = ope_encoder_write_float(enc->value, pcm.value, samplesPerChannel);
    if(enc->HasError("Failed to write to encoder")){
        return;
    }
}

Encoder::~Encoder() {
    if(value) {
        ope_encoder_destroy(value);
        value = nullptr;
    }
}
