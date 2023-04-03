#ifndef OPUSENC_DECODER_H
#define OPUSENC_DECODER_H

#include <opus.h>
#include <nan.h>

namespace bindings {

class Decoder : public Nan::ObjectWrap {
public:
    ~Decoder();
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
private:
    Decoder(OpusDecoder* value);
    OpusDecoder* value;
    Nan::Persistent<v8::ArrayBuffer> pcm;
    int channels;
    static NAN_METHOD(New);
    static NAN_METHOD(Decode);
    static NAN_METHOD(DecodeFloat);
};

}

#endif //OPUSENC_DECODER_H
