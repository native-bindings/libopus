#include "Arguments.h"
#include "Encoder.h"
#include <iostream>
static NAN_METHOD(SetApplication) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v0;
    if(!Arguments::ConvertValue(info[0],v0)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_APPLICATION(v0));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetApplication) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v1;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_APPLICATION(&v1));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v1));
}
static NAN_METHOD(SetBitrate) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v2;
    if(!Arguments::ConvertValue(info[0],v2)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_BITRATE(v2));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetBitrate) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v3;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_BITRATE(&v3));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v3));
}
static NAN_METHOD(SetMaxBandwidth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v4;
    if(!Arguments::ConvertValue(info[0],v4)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_MAX_BANDWIDTH(v4));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetMaxBandwidth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v5;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_MAX_BANDWIDTH(&v5));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v5));
}
static NAN_METHOD(SetVbr) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v6;
    if(!Arguments::ConvertValue(info[0],v6)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_VBR(v6));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetVbr) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v7;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_VBR(&v7));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v7));
}
static NAN_METHOD(SetBandwidth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v8;
    if(!Arguments::ConvertValue(info[0],v8)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_BANDWIDTH(v8));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetBandwidth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v9;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_BANDWIDTH(&v9));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v9));
}
static NAN_METHOD(SetComplexity) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v10;
    if(!Arguments::ConvertValue(info[0],v10)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_COMPLEXITY(v10));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetComplexity) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v11;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_COMPLEXITY(&v11));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v11));
}
static NAN_METHOD(SetInbandFec) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v12;
    if(!Arguments::ConvertValue(info[0],v12)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_INBAND_FEC(v12));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetInbandFec) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v13;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_INBAND_FEC(&v13));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v13));
}
static NAN_METHOD(SetPacketLossPerc) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v14;
    if(!Arguments::ConvertValue(info[0],v14)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PACKET_LOSS_PERC(v14));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetPacketLossPerc) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v15;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PACKET_LOSS_PERC(&v15));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v15));
}
static NAN_METHOD(SetDtx) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v16;
    if(!Arguments::ConvertValue(info[0],v16)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_DTX(v16));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetDtx) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v17;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_DTX(&v17));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v17));
}
static NAN_METHOD(SetVbrConstraint) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v18;
    if(!Arguments::ConvertValue(info[0],v18)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_VBR_CONSTRAINT(v18));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetVbrConstraint) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v19;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_VBR_CONSTRAINT(&v19));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v19));
}
static NAN_METHOD(SetForceChannels) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v20;
    if(!Arguments::ConvertValue(info[0],v20)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_FORCE_CHANNELS(v20));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetForceChannels) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v21;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_FORCE_CHANNELS(&v21));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v21));
}
static NAN_METHOD(SetSignal) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v22;
    if(!Arguments::ConvertValue(info[0],v22)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_SIGNAL(v22));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetSignal) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v23;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_SIGNAL(&v23));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v23));
}
static NAN_METHOD(SetLsbDepth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v24;
    if(!Arguments::ConvertValue(info[0],v24)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_LSB_DEPTH(v24));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetLsbDepth) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v25;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_LSB_DEPTH(&v25));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v25));
}
static NAN_METHOD(SetExpertFrameDuration) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v26;
    if(!Arguments::ConvertValue(info[0],v26)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_EXPERT_FRAME_DURATION(v26));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(SetPredictionDisabled) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v27;
    if(!Arguments::ConvertValue(info[0],v27)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PREDICTION_DISABLED(v27));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
static NAN_METHOD(GetPredictionDisabled) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v28;
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PREDICTION_DISABLED(&v28));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
    info.GetReturnValue().Set(Nan::New(v28));
}
static NAN_METHOD(SetPhaseInversionDisabled) {
    auto* encoder = Arguments::Unwrap<Encoder>(info.This());
    opus_int32 v29;
    if(!Arguments::ConvertValue(info[0],v29)) {
        Nan::ThrowError("Missing argument");
        return;
    }
    encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PHASE_INVERSION_DISABLED(v29));
    if(encoder->error != OPE_OK) {
        Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
        return;
    }
}
void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate>& tpl){
    Nan::SetPrototypeMethod(tpl,"setApplication",SetApplication);
    Nan::SetPrototypeMethod(tpl,"getApplication",GetApplication);
    Nan::SetPrototypeMethod(tpl,"setBitrate",SetBitrate);
    Nan::SetPrototypeMethod(tpl,"getBitrate",GetBitrate);
    Nan::SetPrototypeMethod(tpl,"setMaxBandwidth",SetMaxBandwidth);
    Nan::SetPrototypeMethod(tpl,"getMaxBandwidth",GetMaxBandwidth);
    Nan::SetPrototypeMethod(tpl,"setVbr",SetVbr);
    Nan::SetPrototypeMethod(tpl,"getVbr",GetVbr);
    Nan::SetPrototypeMethod(tpl,"setBandwidth",SetBandwidth);
    Nan::SetPrototypeMethod(tpl,"getBandwidth",GetBandwidth);
    Nan::SetPrototypeMethod(tpl,"setComplexity",SetComplexity);
    Nan::SetPrototypeMethod(tpl,"getComplexity",GetComplexity);
    Nan::SetPrototypeMethod(tpl,"setInbandFec",SetInbandFec);
    Nan::SetPrototypeMethod(tpl,"getInbandFec",GetInbandFec);
    Nan::SetPrototypeMethod(tpl,"setPacketLossPerc",SetPacketLossPerc);
    Nan::SetPrototypeMethod(tpl,"getPacketLossPerc",GetPacketLossPerc);
    Nan::SetPrototypeMethod(tpl,"setDtx",SetDtx);
    Nan::SetPrototypeMethod(tpl,"getDtx",GetDtx);
    Nan::SetPrototypeMethod(tpl,"setVbrConstraint",SetVbrConstraint);
    Nan::SetPrototypeMethod(tpl,"getVbrConstraint",GetVbrConstraint);
    Nan::SetPrototypeMethod(tpl,"setForceChannels",SetForceChannels);
    Nan::SetPrototypeMethod(tpl,"getForceChannels",GetForceChannels);
    Nan::SetPrototypeMethod(tpl,"setSignal",SetSignal);
    Nan::SetPrototypeMethod(tpl,"getSignal",GetSignal);
    Nan::SetPrototypeMethod(tpl,"setLsbDepth",SetLsbDepth);
    Nan::SetPrototypeMethod(tpl,"getLsbDepth",GetLsbDepth);
    Nan::SetPrototypeMethod(tpl,"setExpertFrameDuration",SetExpertFrameDuration);
    Nan::SetPrototypeMethod(tpl,"setPredictionDisabled",SetPredictionDisabled);
    Nan::SetPrototypeMethod(tpl,"getPredictionDisabled",GetPredictionDisabled);
    Nan::SetPrototypeMethod(tpl,"setPhaseInversionDisabled",SetPhaseInversionDisabled);
}
void SetConstants(v8::Local<v8::Object> exports){
    auto constants = Nan::New<v8::Object>();
    Nan::Set(constants,Nan::New("OPUS_OK").ToLocalChecked(),Nan::New(0));
    Nan::Set(constants,Nan::New("OPUS_BAD_ARG").ToLocalChecked(),Nan::New(1));
    Nan::Set(constants,Nan::New("OPUS_BUFFER_TOO_SMALL").ToLocalChecked(),Nan::New(2));
    Nan::Set(constants,Nan::New("OPUS_INTERNAL_ERROR").ToLocalChecked(),Nan::New(3));
    Nan::Set(constants,Nan::New("OPUS_INVALID_PACKET").ToLocalChecked(),Nan::New(4));
    Nan::Set(constants,Nan::New("OPUS_UNIMPLEMENTED").ToLocalChecked(),Nan::New(5));
    Nan::Set(constants,Nan::New("OPUS_INVALID_STATE").ToLocalChecked(),Nan::New(6));
    Nan::Set(constants,Nan::New("OPUS_ALLOC_FAIL").ToLocalChecked(),Nan::New(7));
    Nan::Set(constants,Nan::New("OPUS_SET_APPLICATION_REQUEST").ToLocalChecked(),Nan::New(8));
    Nan::Set(constants,Nan::New("OPUS_GET_APPLICATION_REQUEST").ToLocalChecked(),Nan::New(9));
    Nan::Set(constants,Nan::New("OPUS_SET_BITRATE_REQUEST").ToLocalChecked(),Nan::New(10));
    Nan::Set(constants,Nan::New("OPUS_GET_BITRATE_REQUEST").ToLocalChecked(),Nan::New(11));
    Nan::Set(constants,Nan::New("OPUS_SET_MAX_BANDWIDTH_REQUEST").ToLocalChecked(),Nan::New(12));
    Nan::Set(constants,Nan::New("OPUS_GET_MAX_BANDWIDTH_REQUEST").ToLocalChecked(),Nan::New(13));
    Nan::Set(constants,Nan::New("OPUS_SET_VBR_REQUEST").ToLocalChecked(),Nan::New(14));
    Nan::Set(constants,Nan::New("OPUS_GET_VBR_REQUEST").ToLocalChecked(),Nan::New(15));
    Nan::Set(constants,Nan::New("OPUS_SET_BANDWIDTH_REQUEST").ToLocalChecked(),Nan::New(16));
    Nan::Set(constants,Nan::New("OPUS_GET_BANDWIDTH_REQUEST").ToLocalChecked(),Nan::New(17));
    Nan::Set(constants,Nan::New("OPUS_SET_COMPLEXITY_REQUEST").ToLocalChecked(),Nan::New(18));
    Nan::Set(constants,Nan::New("OPUS_GET_COMPLEXITY_REQUEST").ToLocalChecked(),Nan::New(19));
    Nan::Set(constants,Nan::New("OPUS_SET_INBAND_FEC_REQUEST").ToLocalChecked(),Nan::New(20));
    Nan::Set(constants,Nan::New("OPUS_GET_INBAND_FEC_REQUEST").ToLocalChecked(),Nan::New(21));
    Nan::Set(constants,Nan::New("OPUS_SET_PACKET_LOSS_PERC_REQUEST").ToLocalChecked(),Nan::New(22));
    Nan::Set(constants,Nan::New("OPUS_GET_PACKET_LOSS_PERC_REQUEST").ToLocalChecked(),Nan::New(23));
    Nan::Set(constants,Nan::New("OPUS_SET_DTX_REQUEST").ToLocalChecked(),Nan::New(24));
    Nan::Set(constants,Nan::New("OPUS_GET_DTX_REQUEST").ToLocalChecked(),Nan::New(25));
    Nan::Set(constants,Nan::New("OPUS_SET_VBR_CONSTRAINT_REQUEST").ToLocalChecked(),Nan::New(26));
    Nan::Set(constants,Nan::New("OPUS_GET_VBR_CONSTRAINT_REQUEST").ToLocalChecked(),Nan::New(27));
    Nan::Set(constants,Nan::New("OPUS_SET_FORCE_CHANNELS_REQUEST").ToLocalChecked(),Nan::New(28));
    Nan::Set(constants,Nan::New("OPUS_GET_FORCE_CHANNELS_REQUEST").ToLocalChecked(),Nan::New(29));
    Nan::Set(constants,Nan::New("OPUS_SET_SIGNAL_REQUEST").ToLocalChecked(),Nan::New(30));
    Nan::Set(constants,Nan::New("OPUS_GET_SIGNAL_REQUEST").ToLocalChecked(),Nan::New(31));
    Nan::Set(constants,Nan::New("OPUS_GET_LOOKAHEAD_REQUEST").ToLocalChecked(),Nan::New(32));
    Nan::Set(constants,Nan::New("OPUS_GET_SAMPLE_RATE_REQUEST").ToLocalChecked(),Nan::New(33));
    Nan::Set(constants,Nan::New("OPUS_GET_FINAL_RANGE_REQUEST").ToLocalChecked(),Nan::New(34));
    Nan::Set(constants,Nan::New("OPUS_GET_PITCH_REQUEST").ToLocalChecked(),Nan::New(35));
    Nan::Set(constants,Nan::New("OPUS_SET_GAIN_REQUEST").ToLocalChecked(),Nan::New(36));
    Nan::Set(constants,Nan::New("OPUS_GET_GAIN_REQUEST").ToLocalChecked(),Nan::New(37));
    Nan::Set(constants,Nan::New("OPUS_SET_LSB_DEPTH_REQUEST").ToLocalChecked(),Nan::New(38));
    Nan::Set(constants,Nan::New("OPUS_GET_LSB_DEPTH_REQUEST").ToLocalChecked(),Nan::New(39));
    Nan::Set(constants,Nan::New("OPUS_GET_LAST_PACKET_DURATION_REQUEST").ToLocalChecked(),Nan::New(40));
    Nan::Set(constants,Nan::New("OPUS_SET_EXPERT_FRAME_DURATION_REQUEST").ToLocalChecked(),Nan::New(41));
    Nan::Set(constants,Nan::New("OPUS_GET_EXPERT_FRAME_DURATION_REQUEST").ToLocalChecked(),Nan::New(42));
    Nan::Set(constants,Nan::New("OPUS_SET_PREDICTION_DISABLED_REQUEST").ToLocalChecked(),Nan::New(43));
    Nan::Set(constants,Nan::New("OPUS_GET_PREDICTION_DISABLED_REQUEST").ToLocalChecked(),Nan::New(44));
    Nan::Set(constants,Nan::New("OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST").ToLocalChecked(),Nan::New(45));
    Nan::Set(constants,Nan::New("OPUS_GET_PHASE_INVERSION_DISABLED_REQUEST").ToLocalChecked(),Nan::New(46));
    Nan::Set(constants,Nan::New("OPUS_GET_IN_DTX_REQUEST").ToLocalChecked(),Nan::New(47));
    Nan::Set(constants,Nan::New("OPUS_AUTO").ToLocalChecked(),Nan::New(52));
    Nan::Set(constants,Nan::New("OPUS_BITRATE_MAX").ToLocalChecked(),Nan::New(53));
    Nan::Set(constants,Nan::New("OPUS_APPLICATION_VOIP").ToLocalChecked(),Nan::New(54));
    Nan::Set(constants,Nan::New("OPUS_APPLICATION_AUDIO").ToLocalChecked(),Nan::New(55));
    Nan::Set(constants,Nan::New("OPUS_APPLICATION_RESTRICTED_LOWDELAY").ToLocalChecked(),Nan::New(56));
    Nan::Set(constants,Nan::New("OPUS_SIGNAL_VOICE").ToLocalChecked(),Nan::New(57));
    Nan::Set(constants,Nan::New("OPUS_SIGNAL_MUSIC").ToLocalChecked(),Nan::New(58));
    Nan::Set(constants,Nan::New("OPUS_BANDWIDTH_NARROWBAND").ToLocalChecked(),Nan::New(59));
    Nan::Set(constants,Nan::New("OPUS_BANDWIDTH_MEDIUMBAND").ToLocalChecked(),Nan::New(60));
    Nan::Set(constants,Nan::New("OPUS_BANDWIDTH_WIDEBAND").ToLocalChecked(),Nan::New(61));
    Nan::Set(constants,Nan::New("OPUS_BANDWIDTH_SUPERWIDEBAND").ToLocalChecked(),Nan::New(62));
    Nan::Set(constants,Nan::New("OPUS_BANDWIDTH_FULLBAND").ToLocalChecked(),Nan::New(63));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_ARG").ToLocalChecked(),Nan::New(64));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_2_5_MS").ToLocalChecked(),Nan::New(65));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_5_MS").ToLocalChecked(),Nan::New(66));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_10_MS").ToLocalChecked(),Nan::New(67));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_20_MS").ToLocalChecked(),Nan::New(68));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_40_MS").ToLocalChecked(),Nan::New(69));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_60_MS").ToLocalChecked(),Nan::New(70));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_80_MS").ToLocalChecked(),Nan::New(71));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_100_MS").ToLocalChecked(),Nan::New(72));
    Nan::Set(constants,Nan::New("OPUS_FRAMESIZE_120_MS").ToLocalChecked(),Nan::New(73));
    Nan::Set(constants,Nan::New("OPUS_RESET_STATE").ToLocalChecked(),Nan::New(104));
    Nan::Set(constants,Nan::New("OPE_API_VERSION").ToLocalChecked(),Nan::New(0));
    Nan::Set(constants,Nan::New("OPE_OK").ToLocalChecked(),Nan::New(1));
    Nan::Set(constants,Nan::New("OPE_BAD_ARG").ToLocalChecked(),Nan::New(2));
    Nan::Set(constants,Nan::New("OPE_INTERNAL_ERROR").ToLocalChecked(),Nan::New(3));
    Nan::Set(constants,Nan::New("OPE_UNIMPLEMENTED").ToLocalChecked(),Nan::New(4));
    Nan::Set(constants,Nan::New("OPE_ALLOC_FAIL").ToLocalChecked(),Nan::New(5));
    Nan::Set(constants,Nan::New("OPE_CANNOT_OPEN").ToLocalChecked(),Nan::New(6));
    Nan::Set(constants,Nan::New("OPE_TOO_LATE").ToLocalChecked(),Nan::New(7));
    Nan::Set(constants,Nan::New("OPE_INVALID_PICTURE").ToLocalChecked(),Nan::New(8));
    Nan::Set(constants,Nan::New("OPE_INVALID_ICON").ToLocalChecked(),Nan::New(9));
    Nan::Set(constants,Nan::New("OPE_WRITE_FAIL").ToLocalChecked(),Nan::New(10));
    Nan::Set(constants,Nan::New("OPE_CLOSE_FAIL").ToLocalChecked(),Nan::New(11));
    Nan::Set(constants,Nan::New("OPE_SET_DECISION_DELAY_REQUEST").ToLocalChecked(),Nan::New(12));
    Nan::Set(constants,Nan::New("OPE_GET_DECISION_DELAY_REQUEST").ToLocalChecked(),Nan::New(13));
    Nan::Set(constants,Nan::New("OPE_SET_MUXING_DELAY_REQUEST").ToLocalChecked(),Nan::New(14));
    Nan::Set(constants,Nan::New("OPE_GET_MUXING_DELAY_REQUEST").ToLocalChecked(),Nan::New(15));
    Nan::Set(constants,Nan::New("OPE_SET_COMMENT_PADDING_REQUEST").ToLocalChecked(),Nan::New(16));
    Nan::Set(constants,Nan::New("OPE_GET_COMMENT_PADDING_REQUEST").ToLocalChecked(),Nan::New(17));
    Nan::Set(constants,Nan::New("OPE_SET_SERIALNO_REQUEST").ToLocalChecked(),Nan::New(18));
    Nan::Set(constants,Nan::New("OPE_GET_SERIALNO_REQUEST").ToLocalChecked(),Nan::New(19));
    Nan::Set(constants,Nan::New("OPE_SET_PACKET_CALLBACK_REQUEST").ToLocalChecked(),Nan::New(20));
    Nan::Set(constants,Nan::New("OPE_SET_HEADER_GAIN_REQUEST").ToLocalChecked(),Nan::New(21));
    Nan::Set(constants,Nan::New("OPE_GET_HEADER_GAIN_REQUEST").ToLocalChecked(),Nan::New(22));
    Nan::Set(constants,Nan::New("OPE_GET_NB_STREAMS_REQUEST").ToLocalChecked(),Nan::New(23));
    Nan::Set(constants,Nan::New("OPE_GET_NB_COUPLED_STREAMS_REQUEST").ToLocalChecked(),Nan::New(24));
    Nan::Set(exports,Nan::New("constants").ToLocalChecked(),constants);
}
