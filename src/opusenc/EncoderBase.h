#ifndef NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_
#define NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_

#include <nan.h>

#include <opusenc.h>
namespace bindings::opusenc {

class EncoderBase : public Nan::ObjectWrap {
public:
    OggOpusEnc* value;
    int result;
    static constexpr const char* ClassName = "EncoderBase";
    explicit EncoderBase(OggOpusEnc* value = nullptr);
    ~EncoderBase() override;
    static void SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
};

} // bindings::opusenc
#endif // NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_
