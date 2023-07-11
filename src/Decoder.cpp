#include "Decoder.h"
#include "Arguments.h"

using namespace bindings;

Nan::Persistent<v8::Function> Decoder::constructor;

void Decoder::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Decoder").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetGettersAndSettersPrototypeMethods(tpl);

    Nan::SetPrototypeMethod(tpl,"decode",Decode);
    Nan::SetPrototypeMethod(tpl,"decodeAsync",DecodeAsync);
    Nan::SetPrototypeMethod(tpl,"decodeFloat",DecodeFloat);
    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(exports,Nan::New("Decoder").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Decoder::Decode) {
    Decoder* dec;
    unsigned char *data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    opus_int16* pcm;
    if(
        !Arguments::Unwrap<Decoder>(info.This(), dec) ||
        !Arguments::ConvertValue(info, 0, data) ||
        !Arguments::ConvertValue(info, 1, len) ||
        !Arguments::ConvertValue(info, 2, pcm) ||
        !Arguments::ConvertValue(info, 3, frameSize) ||
        !Arguments::ConvertValue(info, 4, decodeFec)
    ) {
        return;
    }

    int samples = opus_decode(dec->value, data, len, pcm, frameSize, decodeFec);
    if(samples < 0){
        Nan::ThrowError(Nan::New(
            "Failed to decode samples with error: " + std::string(opus_strerror(samples)
        )).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(Decoder::DecodeAsync) {
    Decoder* dec;
    unsigned char *data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    opus_int16* pcm;
    v8::Local<v8::Function> callback;
    if(
        !Arguments::Unwrap<Decoder>(info.This(), dec) ||
        !Arguments::ConvertValue(info, 0, data) ||
        !Arguments::ConvertValue(info, 1, len) ||
        !Arguments::ConvertValue(info, 2, pcm) ||
        !Arguments::ConvertValue(info, 3, frameSize) ||
        !Arguments::ConvertValue(info, 4, decodeFec) ||
        !Arguments::ConvertValue(info, 5, callback)
    ) {
        return;
    }

//    int samples = opus_decode(dec->value, data, len, pcm, frameSize, decodeFec);
//    if(samples < 0){
//        Nan::ThrowError(Nan::New(
//            "Failed to decode samples with error: " + std::string(opus_strerror(samples)
//        )).ToLocalChecked());
//        return;
//    }
//    info.GetReturnValue().Set(Nan::New(samples));
    Nan::AsyncQueueWorker(new DecoderDecodeAsyncWorker(
        new Nan::Callback(callback),
        dec->value,
        data,
        len,
        pcm,
        frameSize,
        decodeFec
    ));
}

NAN_METHOD(Decoder::DecodeFloat) {
    Decoder* dec;
    std::uint8_t *data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    float* pcm;
    if(
        !Arguments::Unwrap<Decoder>(info.This(), dec) ||
        !Arguments::ConvertValue(info, 0, data) ||
        !Arguments::ConvertValue(info, 1, len) ||
        !Arguments::ConvertValue(info, 2, pcm) ||
        !Arguments::ConvertValue(info, 3, frameSize) ||
        !Arguments::ConvertValue(info, 4, decodeFec)
    ){
        return;
    }
    int samples = opus_decode_float(dec->value,data,len,pcm,frameSize,decodeFec);
    if(samples < 0){
        Nan::ThrowError(Nan::New("Failed to decode samples: " + std::string(opus_strerror(samples))).ToLocalChecked());
        return;
    }

    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(Decoder::New){
    opus_int32 sampleRate;
    int channels, error;
    if(
        !Arguments::ConvertValue(info, 0, sampleRate) ||
        !Arguments::ConvertValue(info, 1, channels)
    ) {
        return;
    }
    auto* value = opus_decoder_create(sampleRate,channels,&error);
    if(error != OPUS_OK){
        Nan::ThrowError("Failed to create encoder");
        return;
    };
    auto dec = new Decoder(value, channels);
    dec->Wrap(info.This());
    info.GetReturnValue().Set(info.This());

}

Decoder::Decoder(OpusDecoder* value, int channels): value(value), channels(channels) {
}

Decoder::~Decoder(){
    opus_decoder_destroy(value);
}

DecoderDecodeAsyncWorker::DecoderDecodeAsyncWorker(
    Nan::Callback *callback, OpusDecoder *decoder, unsigned char *data,
    opus_int32 len, opus_int16 *pcm, int frameSize, int decodeFec
):
    Nan::AsyncWorker(callback),
    decoder(decoder),
    data(data),
    len(len),
    pcm(pcm),
    frameSize(frameSize),
    decodeFec(decodeFec)
{

}

void DecoderDecodeAsyncWorker::Execute() {
//    printf("len = %d, frame size = %d\n",len, frameSize);
    result = opus_decode(decoder, data, len, pcm, frameSize, decodeFec);
}

void DecoderDecodeAsyncWorker::HandleOKCallback() {
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
