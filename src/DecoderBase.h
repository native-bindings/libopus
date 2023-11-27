#ifndef NATIVE_BINDINGS_OPUS_DECODER_BASE_H_
#define NATIVE_BINDINGS_OPUS_DECODER_BASE_H_

#include <nan.h>

#include <opus.h>
namespace bindings {

class DecoderBase : public Nan::ObjectWrap {
public:
    OpusDecoder* value;
    int result;
    static constexpr const char* ClassName = "DecoderBase";
    explicit DecoderBase(OpusDecoder* value = nullptr);
    ~DecoderBase() override;
    static void SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
};

} // bindings
#endif // NATIVE_BINDINGS_OPUS_DECODER_BASE_H_
