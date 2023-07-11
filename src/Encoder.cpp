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
    Nan::SetPrototypeMethod(tpl,"encodeAsync",EncodeAsync);
    Nan::SetPrototypeMethod(tpl,"encodeFloat",EncodeFloat);
    SetGettersAndSettersPrototypeMethods(tpl);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(exports,Nan::New("Encoder").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Encoder::New){
    int sampleRate,channels,application, err;
    if(
        !Arguments::ConvertValue(info, 0, sampleRate) ||
        !Arguments::ConvertValue(info, 1, channels)
    ) {
        return;
    }
    if(!bindings::opusenc::ConvertOpusJavaScriptConstant(info[2],application)){
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
    Encoder* enc;
    opus_int32 maxDataBytes;
    opus_int16* pcm;
    int frameSize;
    std::uint8_t* data;

    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0, pcm) ||
        !Arguments::ConvertValue(info, 1, frameSize) ||
        !Arguments::ConvertValue(info, 2, data) ||
        !Arguments::ConvertValue(info, 3, maxDataBytes)
    ){
        return;
    }

    int encodedPacketLengthInBytes = opus_encode(enc->value,pcm,frameSize,data,maxDataBytes);
    if(encodedPacketLengthInBytes < 0){
        Nan::ThrowError(Nan::New(
            "Failed to encode with OPUS error: " + std::string(opus_strerror(encodedPacketLengthInBytes))
        ).ToLocalChecked());
        return;
    }

    info.GetReturnValue().Set(Nan::New(encodedPacketLengthInBytes));

}

NAN_METHOD(Encoder::EncodeAsync){
    Encoder* enc;
    opus_int32 maxDataBytes;
    opus_int16* pcm;
    int frameSize;
    std::uint8_t* data;
    v8::Local<v8::Function> callback;

    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info, 0, pcm) ||
        !Arguments::ConvertValue(info, 1, frameSize) ||
        !Arguments::ConvertValue(info, 2, data) ||
        !Arguments::ConvertValue(info, 3, maxDataBytes) ||
        !Arguments::ConvertValue(info, 4, callback)
    ){
        return;
    }

    auto worker = new EncoderEncodeAsyncWorker(
        new Nan::Callback(callback),
        enc->value,
        pcm,
        frameSize,
        data,
        maxDataBytes
    );
    Nan::AsyncQueueWorker(worker);
//    int encodedPacketLengthInBytes = opus_encode(enc->value,pcm,frameSize,data,maxDataBytes);
//    if(encodedPacketLengthInBytes < 0){
//        Nan::ThrowError(Nan::New(
//            "Failed to encode with OPUS error: " + std::string(opus_strerror(encodedPacketLengthInBytes))
//        ).ToLocalChecked());
//        return;
//    }
//
//    info.GetReturnValue().Set(Nan::New(encodedPacketLengthInBytes));

}

NAN_METHOD(Encoder::EncodeFloat){
    Encoder* enc;
    opus_int32 maxDataBytes;
    float* pcm;
    int frameSize;
    std::uint8_t* data;
    if(
        !Arguments::Unwrap<Encoder>(info.This(), enc) ||
        !Arguments::ConvertValue(info,0,pcm) ||
        !Arguments::ConvertValue(info,1,frameSize) ||
        !Arguments::ConvertValue(info,2,data) ||
        !Arguments::ConvertValue(info,3,maxDataBytes)
    ){
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

EncoderEncodeAsyncWorker::EncoderEncodeAsyncWorker(
    Nan::Callback* callback,
    OpusEncoder* encoder,
    opus_int16 *pcm,
    int frameSize,
    std::uint8_t* data,
    opus_int32 maxDataBytes
):
    Nan::AsyncWorker(callback),
    encoder(encoder),
    maxDataBytes(maxDataBytes),
    pcm(pcm),
    frameSize(frameSize),
    data(data)
{

}

void EncoderEncodeAsyncWorker::Execute() {
    result = opus_encode(encoder, pcm, frameSize, data, maxDataBytes);
}

void EncoderEncodeAsyncWorker::HandleOKCallback() {
    if(result < 0) {
        v8::Local<v8::Value> argv[] = {
            Nan::New(opus_strerror(result)).ToLocalChecked()
        };
        this->callback->Call(1,argv,async_resource);
    } else {
        v8::Local<v8::Value> argv[] = {
            Nan::New(result)
        };
        this->callback->Call(1,argv,async_resource);
    }
}
