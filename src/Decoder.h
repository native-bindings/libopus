#ifndef OPUSENC_DECODER_H
#define OPUSENC_DECODER_H

#include "DecoderBase.h"
#include "core/TypedArrayContents.h"

namespace bindings {

class DecoderDecodeAsyncWorker : public Nan::AsyncWorker {
public:
    DecoderDecodeAsyncWorker(
        Nan::Callback* callback,
        OpusDecoder* decoder,
        v8::Local<v8::Value>& data,
        opus_int32 len,
        v8::Local<v8::Value>& pcm,
        int frameSize,
        int decodeFec
    );
    void Execute() override;
    void HandleOKCallback() override;
private:
    struct Persistent {
        Nan::Persistent<v8::Value> data;
        Nan::Persistent<v8::Value> pcm;
    } persistent;
    OpusDecoder* decoder;
    const TypedArrayContents<unsigned char> input;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    TypedArrayContents<opus_int16> pcm;
    int result = OPUS_OK;
};

class Decoder : public DecoderBase {
public:
    ~Decoder() override;
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
private:
    explicit Decoder(OpusDecoder* value);
    opus_uint32 error = OPUS_OK;
    Nan::Persistent<v8::Local<v8::Object>> pcm;
    static NAN_METHOD(New);
    static NAN_METHOD(Decode);
    static NAN_METHOD(DecodeAsync);
    static NAN_METHOD(DecodeFloat);
};

}

#endif //OPUSENC_DECODER_H
