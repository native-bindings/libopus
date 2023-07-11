#ifndef SRC_OPUSENC_CONSTANTS_H_
#define SRC_OPUSENC_CONSTANTS_H_

#include <nan.h>

namespace bindings {

namespace opusenc {

void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl);
bool ConvertOpusJavaScriptConstant(v8::Local<v8::Value> val, int& out);

}

}

namespace Constants {

void Init(v8::Local<v8::Object> exports);

}

#endif // SRC_OPUSENC_CONSTANTS_H_
