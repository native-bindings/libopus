#ifndef NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_
#define NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_

#include <nan.h>

#include <opus.h>
namespace bindings {

class EncoderBase : public Nan::ObjectWrap {
public:
    OpusEncoder* value;
    int result;
    static constexpr const char* ClassName = "EncoderBase";
    explicit EncoderBase(OpusEncoder* value = nullptr);
    ~EncoderBase() override;
    static void SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
};

} // bindings
#endif // NATIVE_BINDINGS_OPUS_ENCODER_BASE_H_
