#include "OpusFile.h"
#include "core/Arguments.h"

#include <opusfile.h>

using namespace bindings;

Nan::Persistent<v8::Function> OpusFile::constructor;

void OpusFile::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New(ClassName).ToLocalChecked());
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
    const Arguments args(info, "openFile");
    if(!args.Unwrap(file)) {
        return;
    }
    std::string filePath;
    if(!args.Convert(0, filePath)) {
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
    const Arguments args(info, "openMemory");
    if(!args.Unwrap(file)) {
        return;
    }
    TypedArrayContents<std::uint8_t> data;
    if(!args.ConvertTypedArrayContents(0, data)) {
        return;
    }
    int err;
    const auto opusFile = op_open_memory(data.value, data.size, &err);
    if(err != 0 || opusFile == nullptr){
        Nan::ThrowError("Failed to open file");
        return;
    }
    file->reset();
    file->value = opusFile;
}

NAN_METHOD(OpusFile::Read) {
    OpusFile* file;
    const Arguments args(info, "read");
    int li;
    int bufSize;
    TypedArrayContents<std::int16_t> pcm;
    if(!args.Unwrap(file)) {
        return;
    }
    if(!args.ConvertTypedArrayContents(0, pcm)) {
        return;
    }
    if(!Arguments::SafeCast(pcm.size, bufSize, "Sample count")) {
        return;
    }
    auto samples = op_read(file->value, pcm.value, bufSize, &li);
    if(samples < 0) {
        Nan::ThrowError("Failed to read pcm in signed 16-bit format");
        return;
    }
    auto result = Nan::New<v8::Object>();
    Nan::Set(result,Nan::New("sampleCount").ToLocalChecked(), Nan::New(samples));
    Nan::Set(result,Nan::New("linkIndex").ToLocalChecked(), Nan::New(li));
    info.GetReturnValue().Set(result);
}

NAN_METHOD(OpusFile::ReadFloat) {
    OpusFile* file;
    const Arguments args(info, "readFloat");
    TypedArrayContents<std::float_t> pcm;
    int li, bufSize;
    if(!args.Unwrap(file) || !args.ConvertTypedArrayContents(0, pcm)) {
        return;
    }
    if(!Arguments::SafeCast(pcm.size, bufSize, "Sample count")) {
        return;
    }
    const int samples = op_read_float(file->value, pcm.value, bufSize, &li);
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
    TypedArrayContents<std::float_t> pcm;
    int bufSize;
    const Arguments args(info, "readFloatStereo");
    if(!args.Unwrap(file)) {
        return;
    }
    if(!args.ConvertTypedArrayContents(0, pcm)) {
        return;
    }
    if(!Arguments::SafeCast(pcm.size, bufSize, "Sample count")) {
        return;
    }
    auto samples = op_read_float_stereo(file->value, pcm.value, bufSize);
    if(samples < 0) {
        Nan::ThrowError("Failed to read stereo float pcm");
        return;
    }
    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(OpusFile::ChannelCount) {
    OpusFile* file;
    const Arguments args(info, "channelCount");
    if(!args.Unwrap(file)) {
        return;
    }
    int li;
    if(!args.Convert(0, li)) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_channel_count(file->value, li)));
}

NAN_METHOD(OpusFile::LinkCount) {
    OpusFile* file;
    const Arguments args(info, "linkCount");
    if(!args.Unwrap(file)) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_link_count(file->value)));
}

NAN_METHOD(OpusFile::CurrentLink) {
    OpusFile* file;
    const Arguments args(info, "currentLink");
    if(!args.Unwrap(file)) {
        return;
    }
    info.GetReturnValue().Set(Nan::New(op_current_link(file->value)));
}

NAN_METHOD(OpusFile::RawTotal) {
    OpusFile* file;
    const Arguments args(info, "rawTotal");
    if(!args.Unwrap(file)) {
        return;
    }
    int li;
    if(!args.Convert(0, li)) {
        return;
    }
    v8::Local<v8::Value> result;
    if(!Arguments::Get(op_raw_total(file->value, li), result)) {
        return;
    }
    info.GetReturnValue().Set(result);
}

NAN_METHOD(OpusFile::ReadStereo) {
    OpusFile* file;
    const Arguments args(info, "readStereo");
    if(!args.Unwrap(file)) {
        return;
    }
    TypedArrayContents<opus_int16> pcm;
    int bufSize;
    if(!args.ConvertTypedArrayContents(0, pcm) || !Arguments::SafeCast(pcm.size, bufSize, "Sample count")) {
        return;
    }
    const auto samples = op_read_stereo(file->value, pcm.value, bufSize);
    if(samples < 0) {
        Nan::ThrowError("Failed to read stereo pcm in signed 16-bit format");
        return;
    }
    info.GetReturnValue().Set(Nan::New(samples));
}

NAN_METHOD(OpusFile::PcmTell) {
    OpusFile* file;
    const Arguments args(info, "pcmTell");
    if(!args.Unwrap(file)) {
        return;
    }
    const ogg_int64_t offset = op_pcm_tell(file->value);
    if(offset < 0) {
        Nan::ThrowError("op_pcm_tell returned a failure");
        return;
    }
    v8::Local<v8::Value> result;
    if(!Arguments::Get(offset, result)) {
        return;
    }
    info.GetReturnValue().Set(result);
}

NAN_METHOD(OpusFile::PcmSeek) {
    OpusFile* file;
    const Arguments args(info, "pcmSeek");
    if(!args.Unwrap(file)) {
        return;
    }
    opus_int64 offset;
    if(!args.Convert(0, offset)) {
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
    const Arguments args(info, "pcmTotal");
    if(!args.Unwrap(file)) {
        return;
    }
    int li;
    if(!args.Convert(0, li)) {
        return;
    }
    auto result = op_pcm_total(file->value, li);
    if(result < 0) {
        Nan::ThrowError("op_pcm_total returned a failure");
        return;
    }
    v8::Local<v8::Value> value;
    if(!Arguments::Get(result, value)) {
        return;
    }
    info.GetReturnValue().Set(value);
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
