#ifndef OPUSENC_DECODER_H
#define OPUSENC_DECODER_H

#include <opus.h>
#include <nan.h>

class Decoder : public Nan::ObjectWrap {
public:
    ~Decoder();
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
private:
    Decoder();
    OpusDecoder* value = nullptr;
    Nan::Persistent<v8::ArrayBuffer> pcm;
    int channels;
    static NAN_METHOD(New);
    static NAN_METHOD(Decode);
};


#endif //OPUSENC_DECODER_H
