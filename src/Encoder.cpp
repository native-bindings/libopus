#include "Encoder.h"
#include "core/Arguments.h"
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
    Arguments args(info, "constructor");
    int sampleRate,channels,application, err;
    if(
        !args.Convert(0, sampleRate) ||
        !args.Convert(1, channels) ||
        !args.ConvertCustom<int>(2, application, OpusApplicationConstants::Convert)
    ) {
        return;
    }

    OpusEncoder* value = opus_encoder_create(sampleRate,channels,application,&err);
    if(err != OPUS_OK){
        Nan::ThrowError(Nan::New("Failed to create encoder: " + std::string(opus_strerror(err))).ToLocalChecked());
        return;
    }
    auto* enc = new Encoder(value);
    enc->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Encoder::Encode){
    Encoder* enc;
    opus_int32 maxDataBytes;
    TypedArrayContents<opus_int16> pcm;
    int frameSize;
    TypedArrayContents<std::uint8_t> data;
    Arguments args(info, "encode");

    if(
        !args.Unwrap(enc) ||
        !args.ConvertTypedArrayContents(0, pcm) || !args.Convert(1, frameSize) ||
        !args.ConvertTypedArrayContents(2, data) || !args.Convert(3, maxDataBytes)
    ){
        return;
    }

    if(data.size < maxDataBytes) {
        Nan::ThrowError("maxDataBytes must be at least the size of the Int16Array");
        return;
    }

    int encodedPacketLengthInBytes = opus_encode(enc->value, pcm.value, frameSize, data.value, maxDataBytes);
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
//    ConvertTypedArrayContents<opus_int16> pcm;
    int frameSize;
//    ConvertTypedArrayContents<std::uint8_t> data;
    v8::Local<v8::Value> pcm, data;
    v8::Local<v8::Function> callback;
    Arguments args(info, "encodeAsync");

    if(
        !args.Unwrap(enc) ||
        !args.GetArgument(0, pcm) ||
        !args.Convert(1, frameSize) ||
        !args.GetArgument(2, data) ||
        !args.Convert(3, maxDataBytes) ||
        !args.Convert(4, callback)
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
    TypedArrayContents<float> pcm;
    int frameSize;
    TypedArrayContents<std::uint8_t> data;
    Arguments args(info, "encodeFloat");
    if(
        !args.Unwrap(enc) ||
        !args.ConvertTypedArrayContents(0,pcm) ||
        !args.Convert(1,frameSize) ||
        !args.ConvertTypedArrayContents(2,data) ||
        !args.Convert(3,maxDataBytes)
    ){
        return;
    }

    int encodedPacketLengthInBytes = opus_encode_float(enc->value,pcm.value,frameSize,data.value,maxDataBytes);
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
    v8::Local<v8::Value>& input,
    int frameSize,
    v8::Local<v8::Value>& data,
    opus_int32 maxDataBytes
):
    Nan::AsyncWorker(callback),
    encoder(encoder),
    maxDataBytes(maxDataBytes),
    pcm(TypedArrayContents<opus_int16>::New(input)),
    frameSize(frameSize),
    data(TypedArrayContents<std::uint8_t>::New(data)),
    result(OPUS_OK)
{
    SaveToPersistent("pcm", input);
    SaveToPersistent("data", data);
}

void EncoderEncodeAsyncWorker::Execute() {
    result = opus_encode(encoder, pcm.value, frameSize, data.value, maxDataBytes);
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
