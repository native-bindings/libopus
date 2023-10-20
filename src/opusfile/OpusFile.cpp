#include "OpusFile.h"
#include "../Arguments.h"

#include <opusfile.h>

using namespace bindings;

Nan::Persistent<v8::Function> OpusFile::constructor;

void OpusFile::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("OpusFile").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "openFile", OpenFile);
    Nan::SetPrototypeMethod(tpl, "openMemory", OpenMemory);
    Nan::SetPrototypeMethod(tpl, "read", Read);
    Nan::SetPrototypeMethod(tpl, "readStereo", ReadStereo);
    Nan::SetPrototypeMethod(tpl, "readFloat", ReadFloat);
    Nan::SetPrototypeMethod(tpl, "readFloatStereo", ReadFloatStereo);
    Nan::SetPrototypeMethod(tpl, "channelCount", ChannelCount);
    Nan::SetPrototypeMethod(tpl, "linkCount", LinkCount);
    Nan::SetPrototypeMethod(tpl, "currentLink", CurrentLink);
    Nan::SetPrototypeMethod(tpl, "rawTotal", RawTotal);
    Nan::SetPrototypeMethod(tpl, "pcmTotal", PcmTotal);
    Nan::SetPrototypeMethod(tpl, "pcmTell", PcmTell);
    Nan::SetPrototypeMethod(tpl, "pcmSeek", PcmSeek);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(exports,Nan::New("OpusFile").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(OpusFile::OpenFile) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    std::string filePath;
    if(!Arguments::ConvertValue(info, 0, filePath)) {
        return;
    }
    int err;
    auto opusFile = op_open_file(filePath.c_str(), &err);
    if(err != 0 || opusFile == nullptr){
        Nan::ThrowError("Failed to open file");
        return;
    }
    file->reset();
    file->value = opusFile;
}

NAN_METHOD(OpusFile::OpenMemory) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    std::uint8_t* data;
    size_t size;
    if(!Arguments::ConvertValue(info, 0, data, size)) {
        return;
    }
    int err;
    auto opusFile = op_open_memory(data, size, &err);
    if(err != 0 || opusFile == nullptr){
        Nan::ThrowError("Failed to open file");
        return;
    }
    file->reset();
    file->value = opusFile;
}

NAN_METHOD(OpusFile::Read) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    std::int16_t *pcm;
    size_t bufSize;
    if(!Arguments::ConvertValue(info, 0, pcm, bufSize)) {
        return;
    }
    int li;
    auto samples = op_read(file->value, pcm, bufSize, &li);
    if(samples < 0) {
        Nan::ThrowError("Failed to read int16 pcm");
        return;
    }
    auto result = Nan::New<v8::Object>();
    Nan::Set(result,Nan::New("sampleCount").ToLocalChecked(), Nan::New(samples));
    Nan::Set(result,Nan::New("linkIndex").ToLocalChecked(), Nan::New(li));
    info.GetReturnValue().Set(result);
}

NAN_METHOD(OpusFile::ReadFloat) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    float *pcm;
    size_t bufSize;
    if(!Arguments::ConvertValue(info, 0, pcm, bufSize)) {
        return;
    }
    int li;
    auto samples = op_read_float(file->value, pcm, bufSize, &li);
    if(samples < 0) {
        Nan::ThrowError("Failed to read float pcm");
        return;
    }
    auto result = Nan::New<v8::Object>();
    Nan::Set(result,Nan::New("sampleCount").ToLocalChecked(), Nan::New(samples));
    Nan::Set(result,Nan::New("linkIndex").ToLocalChecked(), Nan::New(li));
    info.GetReturnValue().Set(result);
}

NAN_METHOD(OpusFile::ReadFloatStereo) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    float *pcm;
    size_t bufSize;
    if(!Arguments::ConvertValue(info, 0, pcm, bufSize)) {
        return;
    }
    auto samples = op_read_float_stereo(file->value, pcm, bufSize);
    if(samples < 0) {
        Nan::ThrowError("Failed to read stereo float pcm");
        return;
    }
    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(OpusFile::ChannelCount) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    int li;
    if(!Arguments::ConvertValue(info, 0, li)) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_channel_count(file->value, li)));
}

NAN_METHOD(OpusFile::LinkCount) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_link_count(file->value)));
}

NAN_METHOD(OpusFile::CurrentLink) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_current_link(file->value)));
}

NAN_METHOD(OpusFile::RawTotal) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    int li;
    if(!Arguments::ConvertValue(info, 0, li)) {
        return;
    }
    info.GetReturnValue().Set(Nan::New<v8::Number>(op_raw_total(file->value, li)));
}

NAN_METHOD(OpusFile::ReadStereo) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    opus_int16 *pcm;
    size_t bufSize;
    if(!Arguments::ConvertValue(info, 0, pcm, bufSize)) {
        return;
    }
    auto samples = op_read_stereo(file->value, pcm, bufSize);
    if(samples < 0) {
        Nan::ThrowError("Failed to read stereo pcm in signed 16-bit format");
        return;
    }
    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(OpusFile::PcmTell) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    auto result = op_pcm_tell(file->value);
    if(result < 0) {
        Nan::ThrowError("op_pcm_tell returned a failure");
        return;
    }
    info.GetReturnValue().Set(Nan::New<v8::Number>(result));
}

NAN_METHOD(OpusFile::PcmSeek) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    opus_int64 offset;
    if(!Arguments::ConvertValue(info, 0, offset)) {
        return;
    }
    auto result = op_pcm_seek(file->value, offset);
    if(result < 0) {
        Nan::ThrowError("op_pcm_seek returned a failure");
        return;
    }
}

NAN_METHOD(OpusFile::PcmTotal) {
    OpusFile* file;
    if(!Arguments::Unwrap(info.This(), file, "OpusFile")) {
        return;
    }
    int li;
    if(!Arguments::ConvertValue(info, 0, li)) {
        return;
    }
    auto result = op_pcm_total(file->value, li);
    if(result < 0) {
        Nan::ThrowError("op_pcm_total returned a failure");
        return;
    }
    info.GetReturnValue().Set(Nan::New<v8::Number>(result));
}

NAN_METHOD(OpusFile::New) {
    auto f = new OpusFile();
    f->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

OpusFile::~OpusFile() {
    reset();
}

void OpusFile::reset() {
    if(value) {
        op_free(value);
        value = nullptr;
    }
}
