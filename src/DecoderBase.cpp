#include "core/Arguments.h"
#include "DecoderBase.h"

using namespace bindings;

DecoderBase::DecoderBase(OpusDecoder* value): value(value), result(OPUS_OK) {}

DecoderBase::~DecoderBase() {}

static NAN_METHOD(SetApplication) {
    const Arguments args(info, "SetApplication");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_APPLICATION(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_APPLICATION failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetApplication) {
    const Arguments args(info, "GetApplication");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_APPLICATION(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_APPLICATION failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetBitrate) {
    const Arguments args(info, "SetBitrate");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_BITRATE(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_BITRATE failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetBitrate) {
    const Arguments args(info, "GetBitrate");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_BITRATE(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_BITRATE failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetMaxBandwidth) {
    const Arguments args(info, "SetMaxBandwidth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_MAX_BANDWIDTH(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_MAX_BANDWIDTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetMaxBandwidth) {
    const Arguments args(info, "GetMaxBandwidth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_MAX_BANDWIDTH(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_MAX_BANDWIDTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetVbr) {
    const Arguments args(info, "SetVbr");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_VBR(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_VBR failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetVbr) {
    const Arguments args(info, "GetVbr");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_VBR(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_VBR failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetBandwidth) {
    const Arguments args(info, "SetBandwidth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_BANDWIDTH(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_BANDWIDTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetBandwidth) {
    const Arguments args(info, "GetBandwidth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_BANDWIDTH(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_BANDWIDTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetComplexity) {
    const Arguments args(info, "SetComplexity");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_COMPLEXITY(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_COMPLEXITY failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetComplexity) {
    const Arguments args(info, "GetComplexity");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_COMPLEXITY(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_COMPLEXITY failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetInbandFec) {
    const Arguments args(info, "SetInbandFec");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_INBAND_FEC(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_INBAND_FEC failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetInbandFec) {
    const Arguments args(info, "GetInbandFec");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_INBAND_FEC(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_INBAND_FEC failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetPacketLossPerc) {
    const Arguments args(info, "SetPacketLossPerc");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_PACKET_LOSS_PERC(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_PACKET_LOSS_PERC failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetPacketLossPerc) {
    const Arguments args(info, "GetPacketLossPerc");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_PACKET_LOSS_PERC(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_PACKET_LOSS_PERC failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetDtx) {
    const Arguments args(info, "SetDtx");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_DTX(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_DTX failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetDtx) {
    const Arguments args(info, "GetDtx");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_DTX(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_DTX failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetVbrConstraint) {
    const Arguments args(info, "SetVbrConstraint");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_VBR_CONSTRAINT(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_VBR_CONSTRAINT failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetVbrConstraint) {
    const Arguments args(info, "GetVbrConstraint");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_VBR_CONSTRAINT(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_VBR_CONSTRAINT failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetForceChannels) {
    const Arguments args(info, "SetForceChannels");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_FORCE_CHANNELS(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_FORCE_CHANNELS failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetForceChannels) {
    const Arguments args(info, "GetForceChannels");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_FORCE_CHANNELS(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_FORCE_CHANNELS failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetSignal) {
    const Arguments args(info, "SetSignal");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_SIGNAL(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_SIGNAL failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetSignal) {
    const Arguments args(info, "GetSignal");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_SIGNAL(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_SIGNAL failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetLookahead) {
    const Arguments args(info, "GetLookahead");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_LOOKAHEAD(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_LOOKAHEAD failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetSampleRate) {
    const Arguments args(info, "GetSampleRate");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_SAMPLE_RATE(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_SAMPLE_RATE failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetFinalRange) {
    const Arguments args(info, "GetFinalRange");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_uint32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_FINAL_RANGE(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_FINAL_RANGE failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetPitch) {
    const Arguments args(info, "GetPitch");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_PITCH(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_PITCH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetGain) {
    const Arguments args(info, "SetGain");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_GAIN(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_GAIN failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetGain) {
    const Arguments args(info, "GetGain");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_GAIN(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_GAIN failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetLsbDepth) {
    const Arguments args(info, "SetLsbDepth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_LSB_DEPTH(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_LSB_DEPTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetLsbDepth) {
    const Arguments args(info, "GetLsbDepth");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_LSB_DEPTH(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_LSB_DEPTH failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetLastPacketDuration) {
    const Arguments args(info, "GetLastPacketDuration");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_LAST_PACKET_DURATION(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_LAST_PACKET_DURATION failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetExpertFrameDuration) {
    const Arguments args(info, "SetExpertFrameDuration");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_EXPERT_FRAME_DURATION(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_EXPERT_FRAME_DURATION failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetExpertFrameDuration) {
    const Arguments args(info, "GetExpertFrameDuration");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_EXPERT_FRAME_DURATION(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_EXPERT_FRAME_DURATION failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetPredictionDisabled) {
    const Arguments args(info, "SetPredictionDisabled");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_PREDICTION_DISABLED(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_PREDICTION_DISABLED failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetPredictionDisabled) {
    const Arguments args(info, "GetPredictionDisabled");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_PREDICTION_DISABLED(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_PREDICTION_DISABLED failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(SetPhaseInversionDisabled) {
    const Arguments args(info, "SetPhaseInversionDisabled");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 x;
    if(!args.Convert(0, x)) {
        return;
    }
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_SET_PHASE_INVERSION_DISABLED(x));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_SET_PHASE_INVERSION_DISABLED failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetPhaseInversionDisabled) {
    const Arguments args(info, "GetPhaseInversionDisabled");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_PHASE_INVERSION_DISABLED(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_PHASE_INVERSION_DISABLED failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
static NAN_METHOD(GetInDtx) {
    const Arguments args(info, "GetInDtx");
    DecoderBase* decoder;
    if(!args.Unwrap(decoder)) {
        return;
    }
    opus_int32 result;
    auto& status = decoder->result;
    status = opus_decoder_ctl(decoder->value, OPUS_GET_IN_DTX(&result));
    if(status != OPUS_OK) {
        Nan::ThrowError(Nan::New("OPUS_GET_IN_DTX failed with error code " + std::string(opus_strerror(status))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(info.This());
}
void DecoderBase::SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl) {
    Nan::SetPrototypeMethod(tpl, "setApplication", SetApplication);
    Nan::SetPrototypeMethod(tpl, "getApplication", GetApplication);
    Nan::SetPrototypeMethod(tpl, "setBitrate", SetBitrate);
    Nan::SetPrototypeMethod(tpl, "getBitrate", GetBitrate);
    Nan::SetPrototypeMethod(tpl, "setMaxBandwidth", SetMaxBandwidth);
    Nan::SetPrototypeMethod(tpl, "getMaxBandwidth", GetMaxBandwidth);
    Nan::SetPrototypeMethod(tpl, "setVbr", SetVbr);
    Nan::SetPrototypeMethod(tpl, "getVbr", GetVbr);
    Nan::SetPrototypeMethod(tpl, "setBandwidth", SetBandwidth);
    Nan::SetPrototypeMethod(tpl, "getBandwidth", GetBandwidth);
    Nan::SetPrototypeMethod(tpl, "setComplexity", SetComplexity);
    Nan::SetPrototypeMethod(tpl, "getComplexity", GetComplexity);
    Nan::SetPrototypeMethod(tpl, "setInbandFec", SetInbandFec);
    Nan::SetPrototypeMethod(tpl, "getInbandFec", GetInbandFec);
    Nan::SetPrototypeMethod(tpl, "setPacketLossPerc", SetPacketLossPerc);
    Nan::SetPrototypeMethod(tpl, "getPacketLossPerc", GetPacketLossPerc);
    Nan::SetPrototypeMethod(tpl, "setDtx", SetDtx);
    Nan::SetPrototypeMethod(tpl, "getDtx", GetDtx);
    Nan::SetPrototypeMethod(tpl, "setVbrConstraint", SetVbrConstraint);
    Nan::SetPrototypeMethod(tpl, "getVbrConstraint", GetVbrConstraint);
    Nan::SetPrototypeMethod(tpl, "setForceChannels", SetForceChannels);
    Nan::SetPrototypeMethod(tpl, "getForceChannels", GetForceChannels);
    Nan::SetPrototypeMethod(tpl, "setSignal", SetSignal);
    Nan::SetPrototypeMethod(tpl, "getSignal", GetSignal);
    Nan::SetPrototypeMethod(tpl, "getLookahead", GetLookahead);
    Nan::SetPrototypeMethod(tpl, "getSampleRate", GetSampleRate);
    Nan::SetPrototypeMethod(tpl, "getFinalRange", GetFinalRange);
    Nan::SetPrototypeMethod(tpl, "getPitch", GetPitch);
    Nan::SetPrototypeMethod(tpl, "setGain", SetGain);
    Nan::SetPrototypeMethod(tpl, "getGain", GetGain);
    Nan::SetPrototypeMethod(tpl, "setLsbDepth", SetLsbDepth);
    Nan::SetPrototypeMethod(tpl, "getLsbDepth", GetLsbDepth);
    Nan::SetPrototypeMethod(tpl, "getLastPacketDuration", GetLastPacketDuration);
    Nan::SetPrototypeMethod(tpl, "setExpertFrameDuration", SetExpertFrameDuration);
    Nan::SetPrototypeMethod(tpl, "getExpertFrameDuration", GetExpertFrameDuration);
    Nan::SetPrototypeMethod(tpl, "setPredictionDisabled", SetPredictionDisabled);
    Nan::SetPrototypeMethod(tpl, "getPredictionDisabled", GetPredictionDisabled);
    Nan::SetPrototypeMethod(tpl, "setPhaseInversionDisabled", SetPhaseInversionDisabled);
    Nan::SetPrototypeMethod(tpl, "getPhaseInversionDisabled", GetPhaseInversionDisabled);
    Nan::SetPrototypeMethod(tpl, "getInDtx", GetInDtx);
}
