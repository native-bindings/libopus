#ifndef OPUSENC_ENCODER_H
#define OPUSENC_ENCODER_H

#include "core/TypedArrayContents.h"
#include "EncoderBase.h"

#include <nan.h>
#include <opus.h>

namespace bindings {

class EncoderEncodeAsyncWorker : public Nan::AsyncWorker {
public:
    EncoderEncodeAsyncWorker(
        Nan::Callback* callback,
        OpusEncoder* encoder,
        v8::Local<v8::Value>& pcm,
        int frameSize,
        v8::Local<v8::Value>& data,
        opus_int32 maxDataBytes
    );
    void Execute() override;
    void HandleOKCallback() override;
private:
    OpusEncoder* encoder;
    TypedArrayContents<opus_int16> pcm;
    int frameSize;
    TypedArrayContents<std::uint8_t> data;
    opus_int32 maxDataBytes;
    opus_int32 result;
};

class Encoder : public EncoderBase {
public:
    static constexpr const char* ClassName = "Encoder";
    static Nan::Persistent<v8::Function> constructor;
    ~Encoder() final;
    static void Init(v8::Local<v8::Object>);
private:
    OpusEncoder* value;
    Nan::Persistent<v8::ArrayBuffer> encoded;
    explicit Encoder(OpusEncoder*);
    static NAN_METHOD(New);
    static NAN_METHOD(Encode);
    static NAN_METHOD(EncodeAsync);
    static NAN_METHOD(EncodeFloat);
};

}

#endif //OPUSENC_ENCODER_H
