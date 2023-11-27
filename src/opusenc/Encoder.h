#ifndef OPUSENC_ENCODER_H
#define OPUSENC_ENCODER_H

#include "Comments.h"
#include "EncoderBase.h"

namespace bindings::opusenc {

class Encoder final : public EncoderBase {
public:
    static constexpr const char* ClassName = "opusenc.Encoder";
    int error = OPE_OK;
    OggOpusEnc* value = nullptr;
    ~Encoder() override;
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
private:
    bool HasError(std::string&& prefix) const;
    static NAN_METHOD(CreateFile);
    static NAN_METHOD(FlushHeader);
    static NAN_METHOD(Drain);
    static NAN_METHOD(WriteFloat);
    static NAN_METHOD(GetPage);
    static NAN_METHOD(ChainCurrent);
    static NAN_METHOD(ContinueNewFile);
    static NAN_METHOD(Write);
    static NAN_METHOD(CreatePull);
    static NAN_METHOD(New);
    static NAN_METHOD(DeferredInitWithMapping);
};

}

#endif //OPUSENC_ENCODER_H
