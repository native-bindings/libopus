#ifndef OPUSENC_COMMENTS_H
#define OPUSENC_COMMENTS_H

#include <nan.h>
#include <opusenc.h>

class Comments : public Nan::ObjectWrap {
public:
    OggOpusComments* value = nullptr;
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object>);
    ~Comments() override;
private:
    Comments();
    static NAN_METHOD(New);
    static NAN_METHOD(Add);
    static NAN_METHOD(AddPicture);
};


#endif //OPUSENC_COMMENTS_H
