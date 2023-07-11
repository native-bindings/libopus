#ifndef OPUSENC_DECODER_H
#define OPUSENC_DECODER_H

#include <opus.h>
#include <nan.h>

namespace bindings {

class DecoderDecodeAsyncWorker : public Nan::AsyncWorker {
public:
    DecoderDecodeAsyncWorker(
        Nan::Callback* callback,
        OpusDecoder* decoder,
        unsigned char *data,
        opus_int32 len,
        opus_int16* pcm,
        int frameSize,
        int decodeFec
    );
    void Execute() override;
    void HandleOKCallback() override;
private:
    OpusDecoder* decoder;
    unsigned char *data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    opus_int16* pcm;
    int result;
};

class Decoder : public Nan::ObjectWrap {
public:
    ~Decoder();
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
private:
    Decoder(OpusDecoder* value, int channels);
    OpusDecoder* value;
    int channels;
    int error;
    Nan::Persistent<v8::Local<v8::Object>> pcm;
    static NAN_METHOD(New);
    static NAN_METHOD(Decode);
    static NAN_METHOD(DecodeAsync);
    static NAN_METHOD(DecodeFloat);
    // generated methods
    static void SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
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

#endif //OPUSENC_DECODER_H
