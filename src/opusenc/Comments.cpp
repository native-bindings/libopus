#include <stdexcept>

#include "../Arguments.h"
#include "Comments.h"

using namespace bindings::opusenc;

Nan::Persistent<v8::Function> Comments::constructor;

void Comments::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Comments").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl,"add",Add);
    Nan::SetPrototypeMethod(tpl,"addPicture",AddPicture);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(exports,Nan::New("Comments").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Comments::New) {
    auto* comments = new Comments();
    comments->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Comments::Add) {
    Comments* comments;
    std::string tag,value;
    if(
        !Arguments::Unwrap<Comments>(info.This(), comments) ||
        !Arguments::ConvertValue(info, 0, tag) ||
        !Arguments::ConvertValue(info, 1,value)
    ){
        return;
    }
    if(ope_comments_add(comments->value,tag.c_str(),value.c_str()) != OPE_OK){
        Nan::ThrowError("Failed to add comments");
    }
}

NAN_METHOD(Comments::AddPicture) {
    Comments* comments;
    int pictureType;
    std::string filename,description;
    if(
        !Arguments::Unwrap<Comments>(info.This(),comments) ||
        !Arguments::ConvertValue(info, 0, filename) ||
        !Arguments::ConvertValue(info, 1, pictureType) ||
        !Arguments::ConvertValue(info, 2, description)
    ) {
        return;
    }
    if(ope_comments_add_picture(comments->value,filename.c_str(),pictureType,description.c_str()) != OPE_OK){
        Nan::ThrowError("Failed to add comments");
        return;
    }
}

Comments::Comments() {
    value = ope_comments_create();
    if(!value){
        throw std::runtime_error("failed to create comments");
    }
}

Comments::~Comments() {
    ope_comments_destroy(value);
}
