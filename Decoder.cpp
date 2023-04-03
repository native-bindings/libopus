#include "Decoder.h"
#include "Arguments.h"

Nan::Persistent<v8::Function> Decoder::constructor;

void Decoder::Init(v8::Local<v8::Object> exports) {
    auto tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Decoder").ToLocalChecked());
    Nan::SetPrototypeMethod(tpl,"decode",Decode);
    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(exports,Nan::New("Decoder").ToLocalChecked(),Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Decoder::Decode) {
    auto* dec = Arguments::Unwrap<Decoder>(info.This());
    unsigned char *data;
    opus_int32 len;
    int frameSize;
    int decodeFec;
    if(!Arguments::ConvertValue(info[0],data)){
        Nan::ThrowError("First argument must be a valid Uint8Array instance");
        return;
    }
    if(!Arguments::ConvertValue(info[1],len)){
        Nan::ThrowError("Second argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[2],frameSize)){
        Nan::ThrowError("Third argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[3],decodeFec)){
        Nan::ThrowError("Forth argument must be a valid integer");
        return;
    }

    const auto pcmElementCount = frameSize * dec->channels * sizeof(opus_int16);
    opus_int16 pcm[pcmElementCount];

    int samples = opus_decode(dec->value,data,len,pcm,frameSize,decodeFec);
    if(samples < 0){
        Nan::ThrowError("Failed to decode samples");
        return;
    }
    auto buffer = v8::ArrayBuffer::New(
        Nan::GetCurrentContext()->GetIsolate(),
        (pcmElementCount / sizeof(opus_int16)) * sizeof(std::uint8_t)
    );
    dec->pcm.Reset(buffer);
    info.GetReturnValue().Set(v8::Int16Array::New(buffer,0,buffer->ByteLength()));
}

NAN_METHOD(Decoder::New){
    auto dec = new Decoder();
    opus_int32 sampleRate;
    int channels;
    if(!Arguments::ConvertValue(info[0],sampleRate)) {
        Nan::ThrowError("First argument must be a valid integer");
        return;
    }
    if(!Arguments::ConvertValue(info[1],channels)) {
        Nan::ThrowError("First argument must be a valid integer");
        return;
    }
    dec->Wrap(info.This());
    int error;
    dec->channels = channels;
    dec->value = opus_decoder_create(sampleRate,channels,&error);
    if(error != OPUS_OK){
        Nan::ThrowError("Failed to create encoder");
        return;
    }
    info.GetReturnValue().Set(info.This());

}
