#include "src/Encoder.h"
#include "src/Decoder.h"
#include "src/opusenc/opusenc.h"
#include "src/Constants.h"

#include <nan.h>

void Init(v8::Local<v8::Object> exports){
    bindings::Encoder::Init(exports);
    bindings::Decoder::Init(exports);
    bindings::opusenc::Init(exports);
    Constants::Init(exports);
}


NODE_MODULE(NodeOpusEnc,Init);
