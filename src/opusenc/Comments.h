#ifndef OPUSENC_COMMENTS_H
#define OPUSENC_COMMENTS_H

#include <nan.h>
#include <opusenc.h>

namespace bindings::opusenc {

class Comments : public Nan::ObjectWrap {
public:
    static constexpr const char* ClassName = "opusenc.Comments";
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

}

#endif //OPUSENC_COMMENTS_H
