#ifndef OPUSENC_ENCODER_H
#define OPUSENC_ENCODER_H

#include <nan.h>
#include <opus.h>

namespace bindings {

class Encoder : public Nan::ObjectWrap {
public:
    static Nan::Persistent<v8::Function> constructor;
    ~Encoder();
    static void Init(v8::Local<v8::Object>);
private:
    Nan::Persistent<v8::ArrayBuffer> encoded;
    OpusEncoder* value;
    Encoder(OpusEncoder*);
    static NAN_METHOD(New);
    static NAN_METHOD(Encode);
    static NAN_METHOD(EncodeFloat);
};

}

#endif //OPUSENC_ENCODER_H
