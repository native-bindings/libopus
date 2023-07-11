#include "Encoder.h"
#include "Decoder.h"
#include "opusenc/opusenc.h"
#include "Constants.h"

#include <nan.h>

void Init(v8::Local<v8::Object> exports){
    bindings::Encoder::Init(exports);
    bindings::Decoder::Init(exports);
    bindings::opusenc::Init(exports);
    Constants::Init(exports);
}


NODE_MODULE(NodeOpusEnc,Init);
