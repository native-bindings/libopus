#include "Constants.h"

#include <opusenc.h>

static void SetOpusApplicationConstantsConstants(v8::Local<v8::Object> constants) {
    Nan::Set(constants, Nan::New("OPUS_APPLICATION_VOIP").ToLocalChecked(), Nan::New(1));
    Nan::Set(constants, Nan::New("OPUS_APPLICATION_AUDIO").ToLocalChecked(), Nan::New(2));
    Nan::Set(constants, Nan::New("OPUS_APPLICATION_RESTRICTED_LOWDELAY").ToLocalChecked(), Nan::New(3));
}

static void SetOpusBandwidthConstantsConstants(v8::Local<v8::Object> constants) {
    Nan::Set(constants, Nan::New("OPUS_BANDWIDTH_NARROWBAND").ToLocalChecked(), Nan::New(1));
    Nan::Set(constants, Nan::New("OPUS_BANDWIDTH_MEDIUMBAND").ToLocalChecked(), Nan::New(2));
    Nan::Set(constants, Nan::New("OPUS_BANDWIDTH_WIDEBAND").ToLocalChecked(), Nan::New(3));
    Nan::Set(constants, Nan::New("OPUS_BANDWIDTH_SUPERWIDEBAND").ToLocalChecked(), Nan::New(4));
    Nan::Set(constants, Nan::New("OPUS_BANDWIDTH_FULLBAND").ToLocalChecked(), Nan::New(5));
}

static void SetOpusFramesizeConstantsConstants(v8::Local<v8::Object> constants) {
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_ARG").ToLocalChecked(), Nan::New(1));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_2_5_MS").ToLocalChecked(), Nan::New(2));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_5_MS").ToLocalChecked(), Nan::New(3));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_10_MS").ToLocalChecked(), Nan::New(4));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_20_MS").ToLocalChecked(), Nan::New(5));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_40_MS").ToLocalChecked(), Nan::New(6));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_60_MS").ToLocalChecked(), Nan::New(7));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_80_MS").ToLocalChecked(), Nan::New(8));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_100_MS").ToLocalChecked(), Nan::New(9));
    Nan::Set(constants, Nan::New("OPUS_FRAMESIZE_120_MS").ToLocalChecked(), Nan::New(10));
}
void Constants::Init(v8::Local<v8::Object> exports) {
    v8::Local<v8::Object> constants = Nan::New<v8::Object>();
    SetOpusApplicationConstantsConstants(constants);
    SetOpusBandwidthConstantsConstants(constants);
    SetOpusFramesizeConstantsConstants(constants);
    Nan::Set(exports, Nan::New("constants").ToLocalChecked(), constants);
}

bool OpusApplicationConstants::Encode(const std::int32_t& value, v8::Local<v8::Value>& out) {
    if(value == OPUS_APPLICATION_VOIP) {
        out = Nan::New(1);
        return true;
    }
    if(value == OPUS_APPLICATION_AUDIO) {
        out = Nan::New(2);
        return true;
    }
    if(value == OPUS_APPLICATION_RESTRICTED_LOWDELAY) {
        out = Nan::New(3);
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_APPLICATION_VOIP, OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_RESTRICTED_LOWDELAY").ToLocalChecked());
    return false;
}

bool OpusApplicationConstants::Convert(const v8::Local<v8::Value>& uncheckedValue, std::int32_t& out) {
    if(!uncheckedValue->IsInt32()) {
        Nan::ThrowTypeError("value must be an unsigned integer");
        return false;
    }
    const auto value = Nan::To<v8::Int32>(uncheckedValue).ToLocalChecked()->Value();
    if(value == 1) {
        out = OPUS_APPLICATION_VOIP;
        return true;
    }
    if(value == 2) {
        out = OPUS_APPLICATION_AUDIO;
        return true;
    }
    if(value == 3) {
        out = OPUS_APPLICATION_RESTRICTED_LOWDELAY;
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_APPLICATION_VOIP, OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_RESTRICTED_LOWDELAY").ToLocalChecked());
    return false;
}

bool OpusBandwidthConstants::Encode(const std::int32_t& value, v8::Local<v8::Value>& out) {
    if(value == OPUS_BANDWIDTH_NARROWBAND) {
        out = Nan::New(1);
        return true;
    }
    if(value == OPUS_BANDWIDTH_MEDIUMBAND) {
        out = Nan::New(2);
        return true;
    }
    if(value == OPUS_BANDWIDTH_WIDEBAND) {
        out = Nan::New(3);
        return true;
    }
    if(value == OPUS_BANDWIDTH_SUPERWIDEBAND) {
        out = Nan::New(4);
        return true;
    }
    if(value == OPUS_BANDWIDTH_FULLBAND) {
        out = Nan::New(5);
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND").ToLocalChecked());
    return false;
}

bool OpusBandwidthConstants::Convert(const v8::Local<v8::Value>& uncheckedValue, std::int32_t& out) {
    if(!uncheckedValue->IsInt32()) {
        Nan::ThrowTypeError("value must be an unsigned integer");
        return false;
    }
    const auto value = Nan::To<v8::Int32>(uncheckedValue).ToLocalChecked()->Value();
    if(value == 1) {
        out = OPUS_BANDWIDTH_NARROWBAND;
        return true;
    }
    if(value == 2) {
        out = OPUS_BANDWIDTH_MEDIUMBAND;
        return true;
    }
    if(value == 3) {
        out = OPUS_BANDWIDTH_WIDEBAND;
        return true;
    }
    if(value == 4) {
        out = OPUS_BANDWIDTH_SUPERWIDEBAND;
        return true;
    }
    if(value == 5) {
        out = OPUS_BANDWIDTH_FULLBAND;
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND").ToLocalChecked());
    return false;
}

bool OpusFramesizeConstants::Encode(const std::int32_t& value, v8::Local<v8::Value>& out) {
    if(value == OPUS_FRAMESIZE_ARG) {
        out = Nan::New(1);
        return true;
    }
    if(value == OPUS_FRAMESIZE_2_5_MS) {
        out = Nan::New(2);
        return true;
    }
    if(value == OPUS_FRAMESIZE_5_MS) {
        out = Nan::New(3);
        return true;
    }
    if(value == OPUS_FRAMESIZE_10_MS) {
        out = Nan::New(4);
        return true;
    }
    if(value == OPUS_FRAMESIZE_20_MS) {
        out = Nan::New(5);
        return true;
    }
    if(value == OPUS_FRAMESIZE_40_MS) {
        out = Nan::New(6);
        return true;
    }
    if(value == OPUS_FRAMESIZE_60_MS) {
        out = Nan::New(7);
        return true;
    }
    if(value == OPUS_FRAMESIZE_80_MS) {
        out = Nan::New(8);
        return true;
    }
    if(value == OPUS_FRAMESIZE_100_MS) {
        out = Nan::New(9);
        return true;
    }
    if(value == OPUS_FRAMESIZE_120_MS) {
        out = Nan::New(10);
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_FRAMESIZE_ARG, OPUS_FRAMESIZE_2_5_MS, OPUS_FRAMESIZE_5_MS, OPUS_FRAMESIZE_10_MS, OPUS_FRAMESIZE_20_MS, OPUS_FRAMESIZE_40_MS, OPUS_FRAMESIZE_60_MS, OPUS_FRAMESIZE_80_MS, OPUS_FRAMESIZE_100_MS, OPUS_FRAMESIZE_120_MS").ToLocalChecked());
    return false;
}

bool OpusFramesizeConstants::Convert(const v8::Local<v8::Value>& uncheckedValue, std::int32_t& out) {
    if(!uncheckedValue->IsInt32()) {
        Nan::ThrowTypeError("value must be an unsigned integer");
        return false;
    }
    const auto value = Nan::To<v8::Int32>(uncheckedValue).ToLocalChecked()->Value();
    if(value == 1) {
        out = OPUS_FRAMESIZE_ARG;
        return true;
    }
    if(value == 2) {
        out = OPUS_FRAMESIZE_2_5_MS;
        return true;
    }
    if(value == 3) {
        out = OPUS_FRAMESIZE_5_MS;
        return true;
    }
    if(value == 4) {
        out = OPUS_FRAMESIZE_10_MS;
        return true;
    }
    if(value == 5) {
        out = OPUS_FRAMESIZE_20_MS;
        return true;
    }
    if(value == 6) {
        out = OPUS_FRAMESIZE_40_MS;
        return true;
    }
    if(value == 7) {
        out = OPUS_FRAMESIZE_60_MS;
        return true;
    }
    if(value == 8) {
        out = OPUS_FRAMESIZE_80_MS;
        return true;
    }
    if(value == 9) {
        out = OPUS_FRAMESIZE_100_MS;
        return true;
    }
    if(value == 10) {
        out = OPUS_FRAMESIZE_120_MS;
        return true;
    }
    Nan::ThrowError(Nan::New(std::to_string(value) + " does not correspond to any of OPUS_FRAMESIZE_ARG, OPUS_FRAMESIZE_2_5_MS, OPUS_FRAMESIZE_5_MS, OPUS_FRAMESIZE_10_MS, OPUS_FRAMESIZE_20_MS, OPUS_FRAMESIZE_40_MS, OPUS_FRAMESIZE_60_MS, OPUS_FRAMESIZE_80_MS, OPUS_FRAMESIZE_100_MS, OPUS_FRAMESIZE_120_MS").ToLocalChecked());
    return false;
}
