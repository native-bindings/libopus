#include "Encoder.h"
#include "Arguments.h"


Nan::Persistent<v8::Function> Encoder::constructor;

void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate>& tpl);

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
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    if(!AssertNotCreatedEncoder(enc)){
        return;
    }
    int rate,channels,family;
    auto* comments = Arguments::Unwrap<Comments>(info[0]);
    if(!comments){
        Nan::ThrowError("First argument must be a valid Comments instanc");
        return;
    }
    if(!Arguments::ConvertValue(info[1],rate)){
        Nan::ThrowError("Second argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[1],channels)){
        Nan::ThrowError("Third argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[2],family)){
        Nan::ThrowError("Forth argument must be a valid integer");
        return;
    }
    enc->value = ope_encoder_create_pull(comments->value, rate, channels, family, &enc->error);
    if(enc->error != OPE_OK) {
        Nan::ThrowError("Failed to create encoder");
    }

}

NAN_METHOD(Encoder::CreateFile){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    if(!AssertNotCreatedEncoder(enc)){
        return;
    }
    auto* comments = Arguments::Unwrap<Comments>(info[0]);
    if(!comments){
        Nan::ThrowError("First argument must be a valid Comments instance");
        return;
    }
    std::string file;
    if(!Arguments::ConvertValue(info[1],file)){
        Nan::ThrowError("Second argument must be a valid string");
        return;
    }
    int rate,channels,family;
    if(!Arguments::ConvertValue(info[2],rate)){
        Nan::ThrowError("Third argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[3],channels)){
        Nan::ThrowError("Forth argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[4],family)){
        Nan::ThrowError("Fifth argument must be a valid integer");
        return;
    }
    enc->value = ope_encoder_create_file(file.c_str(),comments->value,rate,channels,family,&enc->error);
    if(enc->error){
        enc->value = nullptr;
        Nan::ThrowError("Failed to create direct-file encoder");
    }
}

NAN_METHOD(Encoder::Drain){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    if(ope_encoder_drain(enc->value) != OPE_OK){
        Nan::ThrowError("Failed to drain encoder");
    }

}

NAN_METHOD(Encoder::ChainCurrent){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    auto* comments = Arguments::Unwrap<Comments>(info[0]);
    if(!comments){
        Nan::ThrowError("First argument must be a valid instance of Comments");
        return;
    }
    if(ope_encoder_chain_current(enc->value,comments->value) != OPE_OK){
        Nan::ThrowError("Failed to chain current");
    }
}

NAN_METHOD(Encoder::FlushHeader) {
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    enc->error = ope_encoder_flush_header(enc->value);
    if(enc->error != OPE_OK){
        Nan::ThrowError(Nan::New("Failed to flush header with error: " + std::string(ope_strerror(enc->error))).ToLocalChecked());
    }
}

NAN_METHOD(Encoder::Write){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    std::int16_t* pcm;
    if(!Arguments::ConvertValue(info[0],pcm)){
        Nan::ThrowError("First argument must be a valid Int16Array instance");
        return;
    }
    int samplesPerChannel;
    if(!Arguments::ConvertValue(info[1],samplesPerChannel)){
        Nan::ThrowError("Second argument must have a valid samples per channel");
        return;
    }
    if(ope_encoder_write(enc->value, pcm, samplesPerChannel) != OPE_OK){
        Nan::ThrowError("Failed to write to encoder");
    }

}

NAN_METHOD(Encoder::DeferredInitWithMapping) {
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    int family, streams,coupled_streams;
    if(
        !Arguments::ConvertValue(info[0],family) ||
        !Arguments::ConvertValue(info[1],streams) ||
        !Arguments::ConvertValue(info[2],coupled_streams)
    ){
        Nan::ThrowError("First, second and third arguments must be valid integers");
        return;
    }
    std::uint8_t* mapping;
    if(!Arguments::ConvertValue(info[3],mapping)){
        Nan::ThrowError("Forth argument must be a valid Uint8Array instance");
        return;
    }
    if(ope_encoder_deferred_init_with_mapping(enc->value,family,streams,coupled_streams,mapping) != OPE_OK){
        Nan::ThrowError("ope_encoder_deferred_init_with_mapping call returned a failure");
    }
}

NAN_METHOD(Encoder::ContinueNewFile){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    std::string path;
    if(!Arguments::ConvertValue(info[0],path)){
        Nan::ThrowError("First argument must be a string");
        return;
    }
    Comments* comments;
    if(!Arguments::Unwrap(info[1],comments)){
        Nan::ThrowError("Second argument must be a valid instance of comments");
        return;
    }
    if(ope_encoder_continue_new_file(enc->value, path.c_str(), comments->value) != OPE_OK){
        Nan::ThrowError("Failed to continue new file");
    }
}


NAN_METHOD(Encoder::GetPage) {
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    bool flush;
    if(!Arguments::ConvertValue(info[0],flush)){
        flush = false;
    }
    opus_int32 len;
    unsigned char* page;
    if(ope_encoder_get_page(enc->value,&page,&len,flush ? 1 : 0) != OPE_OK){
        Nan::ThrowError("Failed to get page");
    }
}

NAN_METHOD(Encoder::WriteFloat){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    float* pcm;
    if(!Arguments::ConvertValue(info[0],pcm)){
        Nan::ThrowError("First argument must be a valid Int16Array instance");
        return;
    }
    int samplesPerChannel;
    if(!Arguments::ConvertValue(info[1],samplesPerChannel)){
        Nan::ThrowError("Second argument must have a valid samples per channel");
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
