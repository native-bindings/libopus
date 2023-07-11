#ifndef OPUSENC_ENCODER_H
#define OPUSENC_ENCODER_H

#include <nan.h>
#include <opus.h>

namespace bindings {

class EncoderEncodeAsyncWorker : public Nan::AsyncWorker {
public:
    EncoderEncodeAsyncWorker(
        Nan::Callback* callback,
        OpusEncoder* encoder,
        opus_int16 *pcm,
        int frameSize,
        std::uint8_t* data,
        opus_int32 maxDataBytes
    );
    void Execute() override;
    void HandleOKCallback() override;
private:
    OpusEncoder* encoder;
    opus_int16 *pcm;
    int frameSize;
    std::uint8_t* data;
    opus_int32 maxDataBytes;
    opus_int32 result;
};

class Encoder : public Nan::ObjectWrap {
public:
    static Nan::Persistent<v8::Function> constructor;
    ~Encoder();
    static void Init(v8::Local<v8::Object>);
private:
    int error;
    OpusEncoder* value;
    Nan::Persistent<v8::ArrayBuffer> encoded;
    explicit Encoder(OpusEncoder*);
    static void SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
    static NAN_METHOD(New);
    static NAN_METHOD(Encode);
    static NAN_METHOD(EncodeAsync);
    static NAN_METHOD(EncodeFloat);
    // generated static methods
    static NAN_METHOD(SetApplication);
    static NAN_METHOD(GetApplication);
    static NAN_METHOD(SetBitrate);
    static NAN_METHOD(GetBitrate);
    static NAN_METHOD(SetMaxBandwidth);
    static NAN_METHOD(GetMaxBandwidth);
    static NAN_METHOD(SetVbr);
    static NAN_METHOD(GetVbr);
    static NAN_METHOD(SetBandwidth);
    static NAN_METHOD(GetBandwidth);
    static NAN_METHOD(SetComplexity);
    static NAN_METHOD(GetComplexity);
    static NAN_METHOD(SetInbandFec);
    static NAN_METHOD(GetInbandFec);
    static NAN_METHOD(SetPacketLossPerc);
    static NAN_METHOD(GetPacketLossPerc);
    static NAN_METHOD(SetDtx);
    static NAN_METHOD(GetDtx);
    static NAN_METHOD(SetVbrConstraint);
    static NAN_METHOD(GetVbrConstraint);
    static NAN_METHOD(SetForceChannels);
    static NAN_METHOD(GetForceChannels);
    static NAN_METHOD(SetSignal);
    static NAN_METHOD(GetSignal);
    static NAN_METHOD(GetLookahead);
    static NAN_METHOD(GetSampleRate);
    static NAN_METHOD(GetFinalRange);
    static NAN_METHOD(GetPitch);
    static NAN_METHOD(SetGain);
    static NAN_METHOD(GetGain);
    static NAN_METHOD(SetLsbDepth);
    static NAN_METHOD(GetLsbDepth);
    static NAN_METHOD(GetLastPacketDuration);
    static NAN_METHOD(SetExpertFrameDuration);
    static NAN_METHOD(GetExpertFrameDuration);
    static NAN_METHOD(SetPredictionDisabled);
    static NAN_METHOD(GetPredictionDisabled);
    static NAN_METHOD(SetPhaseInversionDisabled);
    static NAN_METHOD(GetPhaseInversionDisabled);
    static NAN_METHOD(GetInDtx);
};

}

#endif //OPUSENC_ENCODER_H
