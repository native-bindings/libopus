#ifndef OPUSENC_OPUSFILE_H
#define OPUSENC_OPUSFILE_H

#include <opusfile.h>
#include <nan.h>

namespace bindings {

class OpusFile : public Nan::ObjectWrap {
public:
    static Nan::Persistent<v8::Function> constructor;
    static void Init(v8::Local<v8::Object> exports);
private:
    OggOpusFile* value = nullptr;
    /**
     * free `value` memory and set it to nullptr
     */
    void reset();
    ~OpusFile() override;
    static NAN_METHOD(OpenFile);
    static NAN_METHOD(OpenMemory);
    static NAN_METHOD(New);
    static NAN_METHOD(ChannelCount);
    static NAN_METHOD(LinkCount);
    static NAN_METHOD(CurrentLink);
    static NAN_METHOD(RawTotal);
    static NAN_METHOD(Read);
    static NAN_METHOD(ReadStereo);
    static NAN_METHOD(ReadFloat);
    static NAN_METHOD(ReadFloatStereo);
    static NAN_METHOD(PcmTell);
    static NAN_METHOD(PcmSeek);
};

}

#endif //OPUSENC_OPUSFILE_H
