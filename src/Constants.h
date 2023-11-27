#ifndef NATIVE_BINDINGS_OPUS_CONSTANTS_H_
#define NATIVE_BINDINGS_OPUS_CONSTANTS_H_

#include <nan.h>

class Constants {
public:
    static void Init(v8::Local<v8::Object> exports);
};
class OpusApplicationConstants {
public:
    // Convert the original constant to a v8::Local<v8::Value>
    static bool Encode(const std::int32_t& value, v8::Local<v8::Value>&);
    static bool Convert(const v8::Local<v8::Value>&, std::int32_t& value);
};
class OpusBandwidthConstants {
public:
    // Convert the original constant to a v8::Local<v8::Value>
    static bool Encode(const std::int32_t& value, v8::Local<v8::Value>&);
    static bool Convert(const v8::Local<v8::Value>&, std::int32_t& value);
};
class OpusFramesizeConstants {
public:
    // Convert the original constant to a v8::Local<v8::Value>
    static bool Encode(const std::int32_t& value, v8::Local<v8::Value>&);
    static bool Convert(const v8::Local<v8::Value>&, std::int32_t& value);
};
#endif // NATIVE_BINDINGS_OPUS_CONSTANTS_H_
