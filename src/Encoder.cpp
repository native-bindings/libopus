#include "Encoder.h"
#include "Arguments.h"
#include "Constants.h"

#include <nan.h>

using namespace bindings;

Nan::Persistent<v8::Function> Encoder::constructor;

void Encoder::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Encoder").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl,"encode",Encode);
    Nan::SetPrototypeMethod(tpl,"encodeFloat",EncodeFloat);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(exports,Nan::New("Encoder").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Encoder::New){
    int sampleRate,channels,application, err;
    if(!Arguments::ConvertValue(info[0],sampleRate)){
        Nan::ThrowError("First argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[1],channels)){
        Nan::ThrowError("Second argument must be a valid integer");
        return;
    }
    if(!ConvertOpusJavaScriptConstant(info[2],application)){
        Nan::ThrowError("Third argument must be a valid integer");
        return;
    }

    OpusEncoder* value = opus_encoder_create(sampleRate,channels,application,&err);
    if(err != OPUS_OK){
        Nan::ThrowError(Nan::New(
            "Failed to create encoder: " + std::string(opus_strerror(err))
        ).ToLocalChecked());
        return;
    }
    auto* enc = new Encoder(value);
    enc->Wrap(info.This());
    info.GetReturnValue().Set(info.This());

}

NAN_METHOD(Encoder::Encode){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 maxDataBytes;
    opus_int16* pcm;
    int frameSize;
    std::uint8_t* data;

    if(!Arguments::ConvertValue(info[0],pcm)){
        Nan::ThrowError("First argument must be a valid Int16Array");
        return;
    }

    if(!Arguments::ConvertValue(info[1],frameSize)){
        Nan::ThrowError("Second argument must be a valid integer");
        return;
    }

    if(!Arguments::ConvertValue(info[2],data)){
        Nan::ThrowError("Third argument must be a valid instance of Uint8Array");
        return;
    }

    if(!Arguments::ConvertValue(info[3],maxDataBytes)){
        Nan::ThrowError("Forth argument must be a valid integer");
        return;
    }

    int encodedPacketLengthInBytes = opus_encode(enc->value,pcm,frameSize,data,maxDataBytes);
    if(encodedPacketLengthInBytes < 0){
        Nan::ThrowError(Nan::New(
            "Failed to encode with error" + std::string(opus_strerror(encodedPacketLengthInBytes))
        ).ToLocalChecked());
        return;
    }

    info.GetReturnValue().Set(Nan::New(encodedPacketLengthInBytes));

}

NAN_METHOD(Encoder::EncodeFloat){
    auto* enc = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 maxDataBytes;
    float* pcm;
    int frameSize;
    std::uint8_t* data;

    if(!Arguments::ConvertValue(info[0],pcm)){
        Nan::ThrowError("First argument must be a valid Int16Array");
        return;
    }

    if(!Arguments::ConvertValue(info[1],frameSize)){
        Nan::ThrowError("Second argument must be a valid integer");
        return;
    }

    if(!Arguments::ConvertValue(info[2],data)){
        Nan::ThrowError("Third argument must be a valid instance of Uint8Array");
        return;
    }

    if(!Arguments::ConvertValue(info[3],maxDataBytes)){
        Nan::ThrowError("Forth argument must be a valid integer");
        return;
    }

    int encodedPacketLengthInBytes = opus_encode_float(enc->value,pcm,frameSize,data,maxDataBytes);
    if(encodedPacketLengthInBytes < 0){
        Nan::ThrowError(Nan::New(
            "Failed to encode with error: " + std::string(opus_strerror(encodedPacketLengthInBytes))
        ).ToLocalChecked());
        return;
    }

    info.GetReturnValue().Set(Nan::New(encodedPacketLengthInBytes));

}

Encoder::Encoder(OpusEncoder * value): value(value) {

}

Encoder::~Encoder() {
    opus_encoder_destroy(value);
}
