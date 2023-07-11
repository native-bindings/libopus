#include "Encoder.h"
#include "../Arguments.h"
#include "../Constants.h"

using namespace bindings::opusenc;

Nan::Persistent<v8::Function> Encoder::constructor;

static bool AssertNotCreatedEncoder(Encoder* enc){
    if(enc->value){
        Nan::ThrowError("Encoder was already created previously");
        return false;
    }
    return true;
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
    SetEncoderGetterPrototypeMethods(tpl);

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
    if(!AssertNotCreatedEncoder(enc)){
        return;
    }
    int rate,channels,family;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::Unwrap<Comments>(info[0], comments) ||
        !Arguments::ConvertValue(info, 1, rate) ||
        !Arguments::ConvertValue(info, 1, channels) ||
        !Arguments::ConvertValue(info, 2, family)
    ){
        return;
    }
    enc->value = ope_encoder_create_pull(comments->value, rate, channels, family, &enc->error);
    if(enc->error != OPE_OK) {
        Nan::ThrowError("Failed to create encoder");
    }

}

NAN_METHOD(Encoder::CreateFile){
    Encoder* enc;
    if(!Arguments::Unwrap<Encoder>(info.This(), enc)){
        return;
    }
    if(!AssertNotCreatedEncoder(enc)){
        return;
    }
    Comments* comments;
    std::string file;
    int rate,channels,family;
    if(
        !Arguments::Unwrap<Comments>(info, 0, comments) ||
        !Arguments::ConvertValue(info, 1, file) ||
        !Arguments::ConvertValue(info, 2, rate) ||
        !Arguments::ConvertValue(info, 3, channels) ||
        !Arguments::ConvertValue(info, 4, family)
    ){
        return;
    }
    enc->value = ope_encoder_create_file(file.c_str(),comments->value,rate,channels,family,&enc->error);
    if(enc->error){
        enc->value = nullptr;
        Nan::ThrowError("Failed to create direct-file encoder");
    }
}

NAN_METHOD(Encoder::Drain){
    Encoder* enc;
    if(!Arguments::Unwrap<Encoder>(info.This(), enc)){
        return;
    }
    if(ope_encoder_drain(enc->value) != OPE_OK){
        Nan::ThrowError("Failed to drain encoder");
    }

}

NAN_METHOD(Encoder::ChainCurrent){
    Encoder* enc;
    Comments* comments;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::Unwrap<Comments>(info[0], comments)
    ) {
        return;
    }
    if(ope_encoder_chain_current(enc->value,comments->value) != OPE_OK){
        Nan::ThrowError("Failed to chain current");
    }
}

NAN_METHOD(Encoder::FlushHeader) {
    Encoder* enc;
    if(!Arguments::Unwrap<Encoder>(info.This(), enc)){
        return;
    }
    enc->error = ope_encoder_flush_header(enc->value);
    if(enc->error != OPE_OK){
        Nan::ThrowError(Nan::New("Failed to flush header with error: " + std::string(ope_strerror(enc->error))).ToLocalChecked());
    }
}

NAN_METHOD(Encoder::Write){
    Encoder* enc;
    std::int16_t* pcm;
    int samplesPerChannel;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0,pcm) ||
        !Arguments::ConvertValue(info, 1,samplesPerChannel)
    ){
        return;
    }
    if(ope_encoder_write(enc->value, pcm, samplesPerChannel) != OPE_OK){
        Nan::ThrowError("Failed to write to encoder");
    }

}

NAN_METHOD(Encoder::DeferredInitWithMapping) {
    Encoder* enc;
    int family, streams,coupled_streams;
    std::uint8_t* mapping;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0, family) ||
        !Arguments::ConvertValue(info, 1, streams) ||
        !Arguments::ConvertValue(info, 2, coupled_streams) ||
        !Arguments::ConvertValue(info, 3, mapping)
    ){
        Nan::ThrowError("First, second and third arguments must be valid integers");
        return;
    }
    if(ope_encoder_deferred_init_with_mapping(enc->value,family,streams,coupled_streams,mapping) != OPE_OK){
        Nan::ThrowError("ope_encoder_deferred_init_with_mapping call returned a failure");
    }
}

NAN_METHOD(Encoder::ContinueNewFile){
    Encoder* enc;
    Comments* comments;
    std::string path;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0,path) ||
        !Arguments::Unwrap(info, 1,comments)
    ){
        return;
    }
    if(ope_encoder_continue_new_file(enc->value, path.c_str(), comments->value) != OPE_OK){
        Nan::ThrowError("Failed to continue new file");
    }
}


NAN_METHOD(Encoder::GetPage) {
    Encoder* enc;
    bool flush;
    opus_int32 len;
    unsigned char* page;
    if(!Arguments::Unwrap<Encoder>(info.This(), enc)) {
        return;
    }
    if(!Arguments::ConvertValue(info, 0,flush, false)){
        flush = false;
    }
    if(ope_encoder_get_page(enc->value,&page,&len,flush ? 1 : 0) != OPE_OK){
        Nan::ThrowError("Failed to get page");
    }
}

NAN_METHOD(Encoder::WriteFloat){
    Encoder* enc;
    float* pcm;
    int samplesPerChannel;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0, pcm) ||
        !Arguments::ConvertValue(info, 1, samplesPerChannel)
    ) {
        return;
    }
    enc->error = ope_encoder_write_float(enc->value, pcm, samplesPerChannel);
    if(enc->error != OPE_OK){
        Nan::ThrowError("Failed to write to encoder with error");
    }
}

Encoder::Encoder() {

}

Encoder::~Encoder() {
    ope_encoder_destroy(value);
}
