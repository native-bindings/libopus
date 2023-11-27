#include "Decoder.h"
#include "core/Arguments.h"

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
    TypedArrayContents<opus_int16> pcm;
    TypedArrayContents<unsigned char> data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    Arguments args(info, "decode");

    if(
            !args.Unwrap(dec) ||
            !args.ConvertTypedArrayContents(0, data) ||
            !args.Convert(1, len) ||
            !args.ConvertTypedArrayContents(2, pcm) ||
            !args.Convert(3, frameSize) ||
        !args.Convert(4, decodeFec)
    ) {
        return;
    }

    int samples = opus_decode(dec->value, data.value, len, pcm.value, frameSize, decodeFec);
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
    v8::Local<v8::Value> data, pcm;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    v8::Local<v8::Function> callback;
    Arguments args(info, "decodeAsync");
    if(
        !args.Unwrap(dec) ||
        // validate input data
        !args.AssertArgumentType(0, Arguments::IsUint8Array, "Uint8Array") ||
        !args.Convert(1, len) ||
        // validate output data
        !args.AssertArgumentType(2, Arguments::IsInt16Array, "Int16Array") ||
        !args.Convert(3, frameSize) ||
        !args.Convert(4, decodeFec) ||
        !args.Convert(5, callback)
    ) {
        return;
    }
    /**
     * Get first and third argument V8 values
     */
    if(!args.GetArgument(0, data) || !args.GetArgument(2, pcm)) {
        return;
    }

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
    TypedArrayContents<std::uint8_t> inputData;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    TypedArrayContents<float> pcm;
    Arguments args(info, "decodeFloat");
    if(
            !args.Unwrap(dec) ||
            !args.ConvertTypedArrayContents(0, inputData) ||
            !args.Convert(1, len) ||
            !args.ConvertTypedArrayContents(2, pcm) ||
            !args.Convert(3, frameSize) ||
        !args.Convert(4, decodeFec)
    ){
        return;
    }
    int samples = opus_decode_float(dec->value, inputData.value, len, pcm.value, frameSize, decodeFec);
    if(samples < 0){
        Nan::ThrowError(Nan::New("Failed to decode samples: " + std::string(opus_strerror(samples))).ToLocalChecked());
        return;
    }

    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(Decoder::New){
    opus_int32 sampleRate;
    int channels, error;
    const Arguments args(info, "constructor");
    if(
        !args.Convert(0, sampleRate) ||
        !args.Convert(1, channels)
    ) {
        return;
    }
    auto* value = opus_decoder_create(sampleRate,channels,&error);
    if(error != OPUS_OK){
        Nan::ThrowError("Failed to create encoder");
        return;
    }
    auto* dec = new Decoder(value);
    dec->Wrap(info.This());
    info.GetReturnValue().Set(info.This());

}

Decoder::Decoder(OpusDecoder* value): DecoderBase(value) {
}

Decoder::~Decoder(){
    opus_decoder_destroy(value);
    value = nullptr;
}

DecoderDecodeAsyncWorker::DecoderDecodeAsyncWorker(
    Nan::Callback *callback, OpusDecoder *decoder, v8::Local<v8::Value>& data,
    opus_int32 len, v8::Local<v8::Value>& pcm, int frameSize, int decodeFec
):
    Nan::AsyncWorker(callback),
    decoder(decoder),
    persistent({
        data,
        pcm
    }),
    len(len),
    frameSize(frameSize),
    decodeFec(decodeFec),
    input(TypedArrayContents<unsigned char>::New(data)),
    pcm(TypedArrayContents<opus_int16>::New(pcm))
{
}

void DecoderDecodeAsyncWorker::Execute() {
    result = opus_decode(decoder, input.value, len, pcm.value, frameSize, decodeFec);
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
