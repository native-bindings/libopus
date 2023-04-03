#include "Encoder.h"
#include "Comments.h"

namespace bindings::opusenc {

void Init(v8::Local<v8::Object> exports) {
    auto opusenc = Nan::New<v8::Object>();
    Encoder::Init(opusenc);
    Comments::Init(opusenc);
    Nan::Set(exports,Nan::New("opusenc").ToLocalChecked(),opusenc);
}

}