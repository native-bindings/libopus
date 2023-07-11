#include "Encoder.h"
#include "Decoder.h"
#include "Arguments.h"

namespace bindings {
    // static NAN_METHOD(SetApplication);
    // static NAN_METHOD(GetApplication);
    // static NAN_METHOD(SetBitrate);
    // static NAN_METHOD(GetBitrate);
    // static NAN_METHOD(SetMaxBandwidth);
    // static NAN_METHOD(GetMaxBandwidth);
    // static NAN_METHOD(SetVbr);
    // static NAN_METHOD(GetVbr);
    // static NAN_METHOD(SetBandwidth);
    // static NAN_METHOD(GetBandwidth);
    // static NAN_METHOD(SetComplexity);
    // static NAN_METHOD(GetComplexity);
    // static NAN_METHOD(SetInbandFec);
    // static NAN_METHOD(GetInbandFec);
    // static NAN_METHOD(SetPacketLossPerc);
    // static NAN_METHOD(GetPacketLossPerc);
    // static NAN_METHOD(SetDtx);
    // static NAN_METHOD(GetDtx);
    // static NAN_METHOD(SetVbrConstraint);
    // static NAN_METHOD(GetVbrConstraint);
    // static NAN_METHOD(SetForceChannels);
    // static NAN_METHOD(GetForceChannels);
    // static NAN_METHOD(SetSignal);
    // static NAN_METHOD(GetSignal);
    // static NAN_METHOD(GetLookahead);
    // static NAN_METHOD(GetSampleRate);
    // static NAN_METHOD(GetFinalRange);
    // static NAN_METHOD(GetPitch);
    // static NAN_METHOD(SetGain);
    // static NAN_METHOD(GetGain);
    // static NAN_METHOD(SetLsbDepth);
    // static NAN_METHOD(GetLsbDepth);
    // static NAN_METHOD(GetLastPacketDuration);
    // static NAN_METHOD(SetExpertFrameDuration);
    // static NAN_METHOD(GetExpertFrameDuration);
    // static NAN_METHOD(SetPredictionDisabled);
    // static NAN_METHOD(GetPredictionDisabled);
    // static NAN_METHOD(SetPhaseInversionDisabled);
    // static NAN_METHOD(GetPhaseInversionDisabled);
    // static NAN_METHOD(GetInDtx);
    // OPUS_SET_APPLICATION_REQUEST
    NAN_METHOD(Encoder::SetApplication) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v0;
        if(
            !Arguments::ConvertValue(info,0,v0)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_APPLICATION(v0));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v0));
    }
    // OPUS_GET_APPLICATION_REQUEST
    NAN_METHOD(Encoder::GetApplication) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v1;
        if(
            !Arguments::ConvertValue(info,0,v1)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_APPLICATION(&v1));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v1));
    }
    // OPUS_SET_BITRATE_REQUEST
    NAN_METHOD(Encoder::SetBitrate) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v2;
        if(
            !Arguments::ConvertValue(info,0,v2)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_BITRATE(v2));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v2));
    }
    // OPUS_GET_BITRATE_REQUEST
    NAN_METHOD(Encoder::GetBitrate) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v3;
        if(
            !Arguments::ConvertValue(info,0,v3)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_BITRATE(&v3));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v3));
    }
    // OPUS_SET_MAX_BANDWIDTH_REQUEST
    NAN_METHOD(Encoder::SetMaxBandwidth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v4;
        if(
            !Arguments::ConvertValue(info,0,v4)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_MAX_BANDWIDTH(v4));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v4));
    }
    // OPUS_GET_MAX_BANDWIDTH_REQUEST
    NAN_METHOD(Encoder::GetMaxBandwidth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v5;
        if(
            !Arguments::ConvertValue(info,0,v5)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_MAX_BANDWIDTH(&v5));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v5));
    }
    // OPUS_SET_VBR_REQUEST
    NAN_METHOD(Encoder::SetVbr) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v6;
        if(
            !Arguments::ConvertValue(info,0,v6)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_VBR(v6));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v6));
    }
    // OPUS_GET_VBR_REQUEST
    NAN_METHOD(Encoder::GetVbr) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v7;
        if(
            !Arguments::ConvertValue(info,0,v7)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_VBR(&v7));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v7));
    }
    // OPUS_SET_BANDWIDTH_REQUEST
    NAN_METHOD(Encoder::SetBandwidth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v8;
        if(
            !Arguments::ConvertValue(info,0,v8)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_BANDWIDTH(v8));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v8));
    }
    // OPUS_GET_BANDWIDTH_REQUEST
    NAN_METHOD(Encoder::GetBandwidth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v9;
        if(
            !Arguments::ConvertValue(info,0,v9)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_BANDWIDTH(&v9));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v9));
    }
    // OPUS_SET_COMPLEXITY_REQUEST
    NAN_METHOD(Encoder::SetComplexity) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v10;
        if(
            !Arguments::ConvertValue(info,0,v10)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_COMPLEXITY(v10));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v10));
    }
    // OPUS_GET_COMPLEXITY_REQUEST
    NAN_METHOD(Encoder::GetComplexity) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v11;
        if(
            !Arguments::ConvertValue(info,0,v11)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_COMPLEXITY(&v11));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v11));
    }
    // OPUS_SET_INBAND_FEC_REQUEST
    NAN_METHOD(Encoder::SetInbandFec) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v12;
        if(
            !Arguments::ConvertValue(info,0,v12)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_INBAND_FEC(v12));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v12));
    }
    // OPUS_GET_INBAND_FEC_REQUEST
    NAN_METHOD(Encoder::GetInbandFec) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v13;
        if(
            !Arguments::ConvertValue(info,0,v13)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_INBAND_FEC(&v13));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v13));
    }
    // OPUS_SET_PACKET_LOSS_PERC_REQUEST
    NAN_METHOD(Encoder::SetPacketLossPerc) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v14;
        if(
            !Arguments::ConvertValue(info,0,v14)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_PACKET_LOSS_PERC(v14));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v14));
    }
    // OPUS_GET_PACKET_LOSS_PERC_REQUEST
    NAN_METHOD(Encoder::GetPacketLossPerc) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v15;
        if(
            !Arguments::ConvertValue(info,0,v15)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_PACKET_LOSS_PERC(&v15));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v15));
    }
    // OPUS_SET_DTX_REQUEST
    NAN_METHOD(Encoder::SetDtx) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v16;
        if(
            !Arguments::ConvertValue(info,0,v16)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_DTX(v16));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v16));
    }
    // OPUS_GET_DTX_REQUEST
    NAN_METHOD(Encoder::GetDtx) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v17;
        if(
            !Arguments::ConvertValue(info,0,v17)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_DTX(&v17));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v17));
    }
    // OPUS_SET_VBR_CONSTRAINT_REQUEST
    NAN_METHOD(Encoder::SetVbrConstraint) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v18;
        if(
            !Arguments::ConvertValue(info,0,v18)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_VBR_CONSTRAINT(v18));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v18));
    }
    // OPUS_GET_VBR_CONSTRAINT_REQUEST
    NAN_METHOD(Encoder::GetVbrConstraint) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v19;
        if(
            !Arguments::ConvertValue(info,0,v19)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_VBR_CONSTRAINT(&v19));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v19));
    }
    // OPUS_SET_FORCE_CHANNELS_REQUEST
    NAN_METHOD(Encoder::SetForceChannels) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v20;
        if(
            !Arguments::ConvertValue(info,0,v20)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_FORCE_CHANNELS(v20));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v20));
    }
    // OPUS_GET_FORCE_CHANNELS_REQUEST
    NAN_METHOD(Encoder::GetForceChannels) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v21;
        if(
            !Arguments::ConvertValue(info,0,v21)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_FORCE_CHANNELS(&v21));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v21));
    }
    // OPUS_SET_SIGNAL_REQUEST
    NAN_METHOD(Encoder::SetSignal) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v22;
        if(
            !Arguments::ConvertValue(info,0,v22)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_SIGNAL(v22));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v22));
    }
    // OPUS_GET_SIGNAL_REQUEST
    NAN_METHOD(Encoder::GetSignal) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v23;
        if(
            !Arguments::ConvertValue(info,0,v23)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_SIGNAL(&v23));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v23));
    }
    // OPUS_GET_LOOKAHEAD_REQUEST
    NAN_METHOD(Encoder::GetLookahead) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v24;
        if(
            !Arguments::ConvertValue(info,0,v24)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_LOOKAHEAD(&v24));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v24));
    }
    // OPUS_GET_SAMPLE_RATE_REQUEST
    NAN_METHOD(Encoder::GetSampleRate) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v25;
        if(
            !Arguments::ConvertValue(info,0,v25)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_SAMPLE_RATE(&v25));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v25));
    }
    // OPUS_GET_FINAL_RANGE_REQUEST
    NAN_METHOD(Encoder::GetFinalRange) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_uint32 v26;
        if(
            !Arguments::ConvertValue(info,0,v26)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_FINAL_RANGE(&v26));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v26));
    }
    // OPUS_GET_PITCH_REQUEST
    NAN_METHOD(Encoder::GetPitch) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v27;
        if(
            !Arguments::ConvertValue(info,0,v27)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_PITCH(&v27));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v27));
    }
    // OPUS_SET_GAIN_REQUEST
    NAN_METHOD(Encoder::SetGain) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v28;
        if(
            !Arguments::ConvertValue(info,0,v28)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_GAIN(v28));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v28));
    }
    // OPUS_GET_GAIN_REQUEST
    NAN_METHOD(Encoder::GetGain) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v29;
        if(
            !Arguments::ConvertValue(info,0,v29)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_GAIN(&v29));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v29));
    }
    // OPUS_SET_LSB_DEPTH_REQUEST
    NAN_METHOD(Encoder::SetLsbDepth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v30;
        if(
            !Arguments::ConvertValue(info,0,v30)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_LSB_DEPTH(v30));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v30));
    }
    // OPUS_GET_LSB_DEPTH_REQUEST
    NAN_METHOD(Encoder::GetLsbDepth) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v31;
        if(
            !Arguments::ConvertValue(info,0,v31)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_LSB_DEPTH(&v31));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v31));
    }
    // OPUS_GET_LAST_PACKET_DURATION_REQUEST
    NAN_METHOD(Encoder::GetLastPacketDuration) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v32;
        if(
            !Arguments::ConvertValue(info,0,v32)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_LAST_PACKET_DURATION(&v32));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v32));
    }
    // OPUS_SET_EXPERT_FRAME_DURATION_REQUEST
    NAN_METHOD(Encoder::SetExpertFrameDuration) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v33;
        if(
            !Arguments::ConvertValue(info,0,v33)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_EXPERT_FRAME_DURATION(v33));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v33));
    }
    // OPUS_GET_EXPERT_FRAME_DURATION_REQUEST
    NAN_METHOD(Encoder::GetExpertFrameDuration) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v34;
        if(
            !Arguments::ConvertValue(info,0,v34)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_EXPERT_FRAME_DURATION(&v34));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v34));
    }
    // OPUS_SET_PREDICTION_DISABLED_REQUEST
    NAN_METHOD(Encoder::SetPredictionDisabled) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v35;
        if(
            !Arguments::ConvertValue(info,0,v35)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_PREDICTION_DISABLED(v35));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v35));
    }
    // OPUS_GET_PREDICTION_DISABLED_REQUEST
    NAN_METHOD(Encoder::GetPredictionDisabled) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v36;
        if(
            !Arguments::ConvertValue(info,0,v36)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_PREDICTION_DISABLED(&v36));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v36));
    }
    // OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST
    NAN_METHOD(Encoder::SetPhaseInversionDisabled) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v37;
        if(
            !Arguments::ConvertValue(info,0,v37)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_SET_PHASE_INVERSION_DISABLED(v37));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v37));
    }
    // OPUS_GET_PHASE_INVERSION_DISABLED_REQUEST
    NAN_METHOD(Encoder::GetPhaseInversionDisabled) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v38;
        if(
            !Arguments::ConvertValue(info,0,v38)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_PHASE_INVERSION_DISABLED(&v38));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v38));
    }
    // OPUS_GET_IN_DTX_REQUEST
    NAN_METHOD(Encoder::GetInDtx) {
        Encoder* codec;
        if(!Arguments::Unwrap<Encoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v39;
        if(
            !Arguments::ConvertValue(info,0,v39)
        ) {
            return;
        }
        codec->error = opus_encoder_ctl(codec->value,OPUS_GET_IN_DTX(&v39));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_encoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v39));
    }
    // setApplication(value: number): void;
    // getApplication(): number;
    // setBitrate(value: number): void;
    // getBitrate(): number;
    // setMaxBandwidth(value: number): void;
    // getMaxBandwidth(): number;
    // setVbr(value: number): void;
    // getVbr(): number;
    // setBandwidth(value: number): void;
    // getBandwidth(): number;
    // setComplexity(value: number): void;
    // getComplexity(): number;
    // setInbandFec(value: number): void;
    // getInbandFec(): number;
    // setPacketLossPerc(value: number): void;
    // getPacketLossPerc(): number;
    // setDtx(value: number): void;
    // getDtx(): number;
    // setVbrConstraint(value: number): void;
    // getVbrConstraint(): number;
    // setForceChannels(value: number): void;
    // getForceChannels(): number;
    // setSignal(value: number): void;
    // getSignal(): number;
    // getLookahead(): number;
    // getSampleRate(): number;
    // getFinalRange(): number;
    // getPitch(): number;
    // setGain(value: number): void;
    // getGain(): number;
    // setLsbDepth(value: number): void;
    // getLsbDepth(): number;
    // getLastPacketDuration(): number;
    // setExpertFrameDuration(value: number): void;
    // getExpertFrameDuration(): number;
    // setPredictionDisabled(value: number): void;
    // getPredictionDisabled(): number;
    // setPhaseInversionDisabled(value: number): void;
    // getPhaseInversionDisabled(): number;
    // getInDtx(): number;
    void Encoder::SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl) {
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
        Nan::SetPrototypeMethod(tpl,"getLookahead",GetLookahead);
        Nan::SetPrototypeMethod(tpl,"getSampleRate",GetSampleRate);
        Nan::SetPrototypeMethod(tpl,"getFinalRange",GetFinalRange);
        Nan::SetPrototypeMethod(tpl,"getPitch",GetPitch);
        Nan::SetPrototypeMethod(tpl,"setGain",SetGain);
        Nan::SetPrototypeMethod(tpl,"getGain",GetGain);
        Nan::SetPrototypeMethod(tpl,"setLsbDepth",SetLsbDepth);
        Nan::SetPrototypeMethod(tpl,"getLsbDepth",GetLsbDepth);
        Nan::SetPrototypeMethod(tpl,"getLastPacketDuration",GetLastPacketDuration);
        Nan::SetPrototypeMethod(tpl,"setExpertFrameDuration",SetExpertFrameDuration);
        Nan::SetPrototypeMethod(tpl,"getExpertFrameDuration",GetExpertFrameDuration);
        Nan::SetPrototypeMethod(tpl,"setPredictionDisabled",SetPredictionDisabled);
        Nan::SetPrototypeMethod(tpl,"getPredictionDisabled",GetPredictionDisabled);
        Nan::SetPrototypeMethod(tpl,"setPhaseInversionDisabled",SetPhaseInversionDisabled);
        Nan::SetPrototypeMethod(tpl,"getPhaseInversionDisabled",GetPhaseInversionDisabled);
        Nan::SetPrototypeMethod(tpl,"getInDtx",GetInDtx);
    }
    // static NAN_METHOD(SetApplication);
    // static NAN_METHOD(GetApplication);
    // static NAN_METHOD(SetBitrate);
    // static NAN_METHOD(GetBitrate);
    // static NAN_METHOD(SetMaxBandwidth);
    // static NAN_METHOD(GetMaxBandwidth);
    // static NAN_METHOD(SetVbr);
    // static NAN_METHOD(GetVbr);
    // static NAN_METHOD(SetBandwidth);
    // static NAN_METHOD(GetBandwidth);
    // static NAN_METHOD(SetComplexity);
    // static NAN_METHOD(GetComplexity);
    // static NAN_METHOD(SetInbandFec);
    // static NAN_METHOD(GetInbandFec);
    // static NAN_METHOD(SetPacketLossPerc);
    // static NAN_METHOD(GetPacketLossPerc);
    // static NAN_METHOD(SetDtx);
    // static NAN_METHOD(GetDtx);
    // static NAN_METHOD(SetVbrConstraint);
    // static NAN_METHOD(GetVbrConstraint);
    // static NAN_METHOD(SetForceChannels);
    // static NAN_METHOD(GetForceChannels);
    // static NAN_METHOD(SetSignal);
    // static NAN_METHOD(GetSignal);
    // static NAN_METHOD(GetLookahead);
    // static NAN_METHOD(GetSampleRate);
    // static NAN_METHOD(GetFinalRange);
    // static NAN_METHOD(GetPitch);
    // static NAN_METHOD(SetGain);
    // static NAN_METHOD(GetGain);
    // static NAN_METHOD(SetLsbDepth);
    // static NAN_METHOD(GetLsbDepth);
    // static NAN_METHOD(GetLastPacketDuration);
    // static NAN_METHOD(SetExpertFrameDuration);
    // static NAN_METHOD(GetExpertFrameDuration);
    // static NAN_METHOD(SetPredictionDisabled);
    // static NAN_METHOD(GetPredictionDisabled);
    // static NAN_METHOD(SetPhaseInversionDisabled);
    // static NAN_METHOD(GetPhaseInversionDisabled);
    // static NAN_METHOD(GetInDtx);
    // OPUS_SET_APPLICATION_REQUEST
    NAN_METHOD(Decoder::SetApplication) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v40;
        if(
            !Arguments::ConvertValue(info,0,v40)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_APPLICATION(v40));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v40));
    }
    // OPUS_GET_APPLICATION_REQUEST
    NAN_METHOD(Decoder::GetApplication) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v41;
        if(
            !Arguments::ConvertValue(info,0,v41)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_APPLICATION(&v41));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v41));
    }
    // OPUS_SET_BITRATE_REQUEST
    NAN_METHOD(Decoder::SetBitrate) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v42;
        if(
            !Arguments::ConvertValue(info,0,v42)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_BITRATE(v42));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v42));
    }
    // OPUS_GET_BITRATE_REQUEST
    NAN_METHOD(Decoder::GetBitrate) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v43;
        if(
            !Arguments::ConvertValue(info,0,v43)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_BITRATE(&v43));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v43));
    }
    // OPUS_SET_MAX_BANDWIDTH_REQUEST
    NAN_METHOD(Decoder::SetMaxBandwidth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v44;
        if(
            !Arguments::ConvertValue(info,0,v44)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_MAX_BANDWIDTH(v44));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v44));
    }
    // OPUS_GET_MAX_BANDWIDTH_REQUEST
    NAN_METHOD(Decoder::GetMaxBandwidth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v45;
        if(
            !Arguments::ConvertValue(info,0,v45)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_MAX_BANDWIDTH(&v45));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v45));
    }
    // OPUS_SET_VBR_REQUEST
    NAN_METHOD(Decoder::SetVbr) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v46;
        if(
            !Arguments::ConvertValue(info,0,v46)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_VBR(v46));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v46));
    }
    // OPUS_GET_VBR_REQUEST
    NAN_METHOD(Decoder::GetVbr) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v47;
        if(
            !Arguments::ConvertValue(info,0,v47)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_VBR(&v47));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v47));
    }
    // OPUS_SET_BANDWIDTH_REQUEST
    NAN_METHOD(Decoder::SetBandwidth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v48;
        if(
            !Arguments::ConvertValue(info,0,v48)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_BANDWIDTH(v48));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v48));
    }
    // OPUS_GET_BANDWIDTH_REQUEST
    NAN_METHOD(Decoder::GetBandwidth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v49;
        if(
            !Arguments::ConvertValue(info,0,v49)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_BANDWIDTH(&v49));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v49));
    }
    // OPUS_SET_COMPLEXITY_REQUEST
    NAN_METHOD(Decoder::SetComplexity) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v50;
        if(
            !Arguments::ConvertValue(info,0,v50)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_COMPLEXITY(v50));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v50));
    }
    // OPUS_GET_COMPLEXITY_REQUEST
    NAN_METHOD(Decoder::GetComplexity) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v51;
        if(
            !Arguments::ConvertValue(info,0,v51)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_COMPLEXITY(&v51));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v51));
    }
    // OPUS_SET_INBAND_FEC_REQUEST
    NAN_METHOD(Decoder::SetInbandFec) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v52;
        if(
            !Arguments::ConvertValue(info,0,v52)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_INBAND_FEC(v52));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v52));
    }
    // OPUS_GET_INBAND_FEC_REQUEST
    NAN_METHOD(Decoder::GetInbandFec) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v53;
        if(
            !Arguments::ConvertValue(info,0,v53)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_INBAND_FEC(&v53));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v53));
    }
    // OPUS_SET_PACKET_LOSS_PERC_REQUEST
    NAN_METHOD(Decoder::SetPacketLossPerc) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v54;
        if(
            !Arguments::ConvertValue(info,0,v54)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_PACKET_LOSS_PERC(v54));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v54));
    }
    // OPUS_GET_PACKET_LOSS_PERC_REQUEST
    NAN_METHOD(Decoder::GetPacketLossPerc) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v55;
        if(
            !Arguments::ConvertValue(info,0,v55)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_PACKET_LOSS_PERC(&v55));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v55));
    }
    // OPUS_SET_DTX_REQUEST
    NAN_METHOD(Decoder::SetDtx) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v56;
        if(
            !Arguments::ConvertValue(info,0,v56)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_DTX(v56));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v56));
    }
    // OPUS_GET_DTX_REQUEST
    NAN_METHOD(Decoder::GetDtx) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v57;
        if(
            !Arguments::ConvertValue(info,0,v57)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_DTX(&v57));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v57));
    }
    // OPUS_SET_VBR_CONSTRAINT_REQUEST
    NAN_METHOD(Decoder::SetVbrConstraint) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v58;
        if(
            !Arguments::ConvertValue(info,0,v58)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_VBR_CONSTRAINT(v58));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v58));
    }
    // OPUS_GET_VBR_CONSTRAINT_REQUEST
    NAN_METHOD(Decoder::GetVbrConstraint) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v59;
        if(
            !Arguments::ConvertValue(info,0,v59)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_VBR_CONSTRAINT(&v59));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v59));
    }
    // OPUS_SET_FORCE_CHANNELS_REQUEST
    NAN_METHOD(Decoder::SetForceChannels) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v60;
        if(
            !Arguments::ConvertValue(info,0,v60)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_FORCE_CHANNELS(v60));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v60));
    }
    // OPUS_GET_FORCE_CHANNELS_REQUEST
    NAN_METHOD(Decoder::GetForceChannels) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v61;
        if(
            !Arguments::ConvertValue(info,0,v61)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_FORCE_CHANNELS(&v61));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v61));
    }
    // OPUS_SET_SIGNAL_REQUEST
    NAN_METHOD(Decoder::SetSignal) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v62;
        if(
            !Arguments::ConvertValue(info,0,v62)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_SIGNAL(v62));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v62));
    }
    // OPUS_GET_SIGNAL_REQUEST
    NAN_METHOD(Decoder::GetSignal) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v63;
        if(
            !Arguments::ConvertValue(info,0,v63)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_SIGNAL(&v63));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v63));
    }
    // OPUS_GET_LOOKAHEAD_REQUEST
    NAN_METHOD(Decoder::GetLookahead) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v64;
        if(
            !Arguments::ConvertValue(info,0,v64)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_LOOKAHEAD(&v64));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v64));
    }
    // OPUS_GET_SAMPLE_RATE_REQUEST
    NAN_METHOD(Decoder::GetSampleRate) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v65;
        if(
            !Arguments::ConvertValue(info,0,v65)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_SAMPLE_RATE(&v65));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v65));
    }
    // OPUS_GET_FINAL_RANGE_REQUEST
    NAN_METHOD(Decoder::GetFinalRange) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_uint32 v66;
        if(
            !Arguments::ConvertValue(info,0,v66)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_FINAL_RANGE(&v66));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v66));
    }
    // OPUS_GET_PITCH_REQUEST
    NAN_METHOD(Decoder::GetPitch) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v67;
        if(
            !Arguments::ConvertValue(info,0,v67)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_PITCH(&v67));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v67));
    }
    // OPUS_SET_GAIN_REQUEST
    NAN_METHOD(Decoder::SetGain) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v68;
        if(
            !Arguments::ConvertValue(info,0,v68)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_GAIN(v68));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v68));
    }
    // OPUS_GET_GAIN_REQUEST
    NAN_METHOD(Decoder::GetGain) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v69;
        if(
            !Arguments::ConvertValue(info,0,v69)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_GAIN(&v69));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v69));
    }
    // OPUS_SET_LSB_DEPTH_REQUEST
    NAN_METHOD(Decoder::SetLsbDepth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v70;
        if(
            !Arguments::ConvertValue(info,0,v70)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_LSB_DEPTH(v70));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v70));
    }
    // OPUS_GET_LSB_DEPTH_REQUEST
    NAN_METHOD(Decoder::GetLsbDepth) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v71;
        if(
            !Arguments::ConvertValue(info,0,v71)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_LSB_DEPTH(&v71));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v71));
    }
    // OPUS_GET_LAST_PACKET_DURATION_REQUEST
    NAN_METHOD(Decoder::GetLastPacketDuration) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v72;
        if(
            !Arguments::ConvertValue(info,0,v72)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_LAST_PACKET_DURATION(&v72));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v72));
    }
    // OPUS_SET_EXPERT_FRAME_DURATION_REQUEST
    NAN_METHOD(Decoder::SetExpertFrameDuration) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v73;
        if(
            !Arguments::ConvertValue(info,0,v73)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_EXPERT_FRAME_DURATION(v73));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v73));
    }
    // OPUS_GET_EXPERT_FRAME_DURATION_REQUEST
    NAN_METHOD(Decoder::GetExpertFrameDuration) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v74;
        if(
            !Arguments::ConvertValue(info,0,v74)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_EXPERT_FRAME_DURATION(&v74));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v74));
    }
    // OPUS_SET_PREDICTION_DISABLED_REQUEST
    NAN_METHOD(Decoder::SetPredictionDisabled) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v75;
        if(
            !Arguments::ConvertValue(info,0,v75)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_PREDICTION_DISABLED(v75));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v75));
    }
    // OPUS_GET_PREDICTION_DISABLED_REQUEST
    NAN_METHOD(Decoder::GetPredictionDisabled) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v76;
        if(
            !Arguments::ConvertValue(info,0,v76)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_PREDICTION_DISABLED(&v76));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v76));
    }
    // OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST
    NAN_METHOD(Decoder::SetPhaseInversionDisabled) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v77;
        if(
            !Arguments::ConvertValue(info,0,v77)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_SET_PHASE_INVERSION_DISABLED(v77));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v77));
    }
    // OPUS_GET_PHASE_INVERSION_DISABLED_REQUEST
    NAN_METHOD(Decoder::GetPhaseInversionDisabled) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v78;
        if(
            !Arguments::ConvertValue(info,0,v78)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_PHASE_INVERSION_DISABLED(&v78));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v78));
    }
    // OPUS_GET_IN_DTX_REQUEST
    NAN_METHOD(Decoder::GetInDtx) {
        Decoder* codec;
        if(!Arguments::Unwrap<Decoder>(info.This(), codec)) {
            return;
        }
        opus_int32 v79;
        if(
            !Arguments::ConvertValue(info,0,v79)
        ) {
            return;
        }
        codec->error = opus_decoder_ctl(codec->value,OPUS_GET_IN_DTX(&v79));
        if(codec->error != OPUS_OK) {
            Nan::ThrowError(Nan::New("Failed to call opus_decoder_ctl with error: " + std::string(opus_strerror(codec->error))).ToLocalChecked());
            return;
        }
        info.GetReturnValue().Set(Nan::New(v79));
    }
    // setApplication(value: number): void;
    // getApplication(): number;
    // setBitrate(value: number): void;
    // getBitrate(): number;
    // setMaxBandwidth(value: number): void;
    // getMaxBandwidth(): number;
    // setVbr(value: number): void;
    // getVbr(): number;
    // setBandwidth(value: number): void;
    // getBandwidth(): number;
    // setComplexity(value: number): void;
    // getComplexity(): number;
    // setInbandFec(value: number): void;
    // getInbandFec(): number;
    // setPacketLossPerc(value: number): void;
    // getPacketLossPerc(): number;
    // setDtx(value: number): void;
    // getDtx(): number;
    // setVbrConstraint(value: number): void;
    // getVbrConstraint(): number;
    // setForceChannels(value: number): void;
    // getForceChannels(): number;
    // setSignal(value: number): void;
    // getSignal(): number;
    // getLookahead(): number;
    // getSampleRate(): number;
    // getFinalRange(): number;
    // getPitch(): number;
    // setGain(value: number): void;
    // getGain(): number;
    // setLsbDepth(value: number): void;
    // getLsbDepth(): number;
    // getLastPacketDuration(): number;
    // setExpertFrameDuration(value: number): void;
    // getExpertFrameDuration(): number;
    // setPredictionDisabled(value: number): void;
    // getPredictionDisabled(): number;
    // setPhaseInversionDisabled(value: number): void;
    // getPhaseInversionDisabled(): number;
    // getInDtx(): number;
    void Decoder::SetGettersAndSettersPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl) {
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
        Nan::SetPrototypeMethod(tpl,"getLookahead",GetLookahead);
        Nan::SetPrototypeMethod(tpl,"getSampleRate",GetSampleRate);
        Nan::SetPrototypeMethod(tpl,"getFinalRange",GetFinalRange);
        Nan::SetPrototypeMethod(tpl,"getPitch",GetPitch);
        Nan::SetPrototypeMethod(tpl,"setGain",SetGain);
        Nan::SetPrototypeMethod(tpl,"getGain",GetGain);
        Nan::SetPrototypeMethod(tpl,"setLsbDepth",SetLsbDepth);
        Nan::SetPrototypeMethod(tpl,"getLsbDepth",GetLsbDepth);
        Nan::SetPrototypeMethod(tpl,"getLastPacketDuration",GetLastPacketDuration);
        Nan::SetPrototypeMethod(tpl,"setExpertFrameDuration",SetExpertFrameDuration);
        Nan::SetPrototypeMethod(tpl,"getExpertFrameDuration",GetExpertFrameDuration);
        Nan::SetPrototypeMethod(tpl,"setPredictionDisabled",SetPredictionDisabled);
        Nan::SetPrototypeMethod(tpl,"getPredictionDisabled",GetPredictionDisabled);
        Nan::SetPrototypeMethod(tpl,"setPhaseInversionDisabled",SetPhaseInversionDisabled);
        Nan::SetPrototypeMethod(tpl,"getPhaseInversionDisabled",GetPhaseInversionDisabled);
        Nan::SetPrototypeMethod(tpl,"getInDtx",GetInDtx);
    }
}
