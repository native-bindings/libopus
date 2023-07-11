#include "Arguments.h"
#include "opusenc/Encoder.h"

namespace Constants {
    void Init(v8::Local<v8::Object> exports){
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
        Nan::Set(constants,Nan::New("OPE_API_VERSION").ToLocalChecked(),Nan::New(115));
        Nan::Set(constants,Nan::New("OPE_OK").ToLocalChecked(),Nan::New(116));
        Nan::Set(constants,Nan::New("OPE_BAD_ARG").ToLocalChecked(),Nan::New(117));
        Nan::Set(constants,Nan::New("OPE_INTERNAL_ERROR").ToLocalChecked(),Nan::New(118));
        Nan::Set(constants,Nan::New("OPE_UNIMPLEMENTED").ToLocalChecked(),Nan::New(119));
        Nan::Set(constants,Nan::New("OPE_ALLOC_FAIL").ToLocalChecked(),Nan::New(120));
        Nan::Set(constants,Nan::New("OPE_CANNOT_OPEN").ToLocalChecked(),Nan::New(121));
        Nan::Set(constants,Nan::New("OPE_TOO_LATE").ToLocalChecked(),Nan::New(122));
        Nan::Set(constants,Nan::New("OPE_INVALID_PICTURE").ToLocalChecked(),Nan::New(123));
        Nan::Set(constants,Nan::New("OPE_INVALID_ICON").ToLocalChecked(),Nan::New(124));
        Nan::Set(constants,Nan::New("OPE_WRITE_FAIL").ToLocalChecked(),Nan::New(125));
        Nan::Set(constants,Nan::New("OPE_CLOSE_FAIL").ToLocalChecked(),Nan::New(126));
        Nan::Set(constants,Nan::New("OPE_SET_DECISION_DELAY_REQUEST").ToLocalChecked(),Nan::New(127));
        Nan::Set(constants,Nan::New("OPE_GET_DECISION_DELAY_REQUEST").ToLocalChecked(),Nan::New(128));
        Nan::Set(constants,Nan::New("OPE_SET_MUXING_DELAY_REQUEST").ToLocalChecked(),Nan::New(129));
        Nan::Set(constants,Nan::New("OPE_GET_MUXING_DELAY_REQUEST").ToLocalChecked(),Nan::New(130));
        Nan::Set(constants,Nan::New("OPE_SET_COMMENT_PADDING_REQUEST").ToLocalChecked(),Nan::New(131));
        Nan::Set(constants,Nan::New("OPE_GET_COMMENT_PADDING_REQUEST").ToLocalChecked(),Nan::New(132));
        Nan::Set(constants,Nan::New("OPE_SET_SERIALNO_REQUEST").ToLocalChecked(),Nan::New(133));
        Nan::Set(constants,Nan::New("OPE_GET_SERIALNO_REQUEST").ToLocalChecked(),Nan::New(134));
        Nan::Set(constants,Nan::New("OPE_SET_PACKET_CALLBACK_REQUEST").ToLocalChecked(),Nan::New(135));
        Nan::Set(constants,Nan::New("OPE_SET_HEADER_GAIN_REQUEST").ToLocalChecked(),Nan::New(136));
        Nan::Set(constants,Nan::New("OPE_GET_HEADER_GAIN_REQUEST").ToLocalChecked(),Nan::New(137));
        Nan::Set(constants,Nan::New("OPE_GET_NB_STREAMS_REQUEST").ToLocalChecked(),Nan::New(138));
        Nan::Set(constants,Nan::New("OPE_GET_NB_COUPLED_STREAMS_REQUEST").ToLocalChecked(),Nan::New(139));
        Nan::Set(exports,Nan::New("constants").ToLocalChecked(),constants);
    }
}
namespace bindings::opusenc {
    bool ConvertOpusJavaScriptConstant(v8::Local<v8::Value> val, int& out) {
        if(!val->IsNumber()) return false;
        const auto n = Nan::To<v8::Number>(val).ToLocalChecked()->Value();
        if(n == 0) {
            out = OPUS_OK;
            return true;
        }
        if(n == 1) {
            out = OPUS_BAD_ARG;
            return true;
        }
        if(n == 2) {
            out = OPUS_BUFFER_TOO_SMALL;
            return true;
        }
        if(n == 3) {
            out = OPUS_INTERNAL_ERROR;
            return true;
        }
        if(n == 4) {
            out = OPUS_INVALID_PACKET;
            return true;
        }
        if(n == 5) {
            out = OPUS_UNIMPLEMENTED;
            return true;
        }
        if(n == 6) {
            out = OPUS_INVALID_STATE;
            return true;
        }
        if(n == 7) {
            out = OPUS_ALLOC_FAIL;
            return true;
        }
        if(n == 8) {
            out = OPUS_SET_APPLICATION_REQUEST;
            return true;
        }
        if(n == 9) {
            out = OPUS_GET_APPLICATION_REQUEST;
            return true;
        }
        if(n == 10) {
            out = OPUS_SET_BITRATE_REQUEST;
            return true;
        }
        if(n == 11) {
            out = OPUS_GET_BITRATE_REQUEST;
            return true;
        }
        if(n == 12) {
            out = OPUS_SET_MAX_BANDWIDTH_REQUEST;
            return true;
        }
        if(n == 13) {
            out = OPUS_GET_MAX_BANDWIDTH_REQUEST;
            return true;
        }
        if(n == 14) {
            out = OPUS_SET_VBR_REQUEST;
            return true;
        }
        if(n == 15) {
            out = OPUS_GET_VBR_REQUEST;
            return true;
        }
        if(n == 16) {
            out = OPUS_SET_BANDWIDTH_REQUEST;
            return true;
        }
        if(n == 17) {
            out = OPUS_GET_BANDWIDTH_REQUEST;
            return true;
        }
        if(n == 18) {
            out = OPUS_SET_COMPLEXITY_REQUEST;
            return true;
        }
        if(n == 19) {
            out = OPUS_GET_COMPLEXITY_REQUEST;
            return true;
        }
        if(n == 20) {
            out = OPUS_SET_INBAND_FEC_REQUEST;
            return true;
        }
        if(n == 21) {
            out = OPUS_GET_INBAND_FEC_REQUEST;
            return true;
        }
        if(n == 22) {
            out = OPUS_SET_PACKET_LOSS_PERC_REQUEST;
            return true;
        }
        if(n == 23) {
            out = OPUS_GET_PACKET_LOSS_PERC_REQUEST;
            return true;
        }
        if(n == 24) {
            out = OPUS_SET_DTX_REQUEST;
            return true;
        }
        if(n == 25) {
            out = OPUS_GET_DTX_REQUEST;
            return true;
        }
        if(n == 26) {
            out = OPUS_SET_VBR_CONSTRAINT_REQUEST;
            return true;
        }
        if(n == 27) {
            out = OPUS_GET_VBR_CONSTRAINT_REQUEST;
            return true;
        }
        if(n == 28) {
            out = OPUS_SET_FORCE_CHANNELS_REQUEST;
            return true;
        }
        if(n == 29) {
            out = OPUS_GET_FORCE_CHANNELS_REQUEST;
            return true;
        }
        if(n == 30) {
            out = OPUS_SET_SIGNAL_REQUEST;
            return true;
        }
        if(n == 31) {
            out = OPUS_GET_SIGNAL_REQUEST;
            return true;
        }
        if(n == 32) {
            out = OPUS_GET_LOOKAHEAD_REQUEST;
            return true;
        }
        if(n == 33) {
            out = OPUS_GET_SAMPLE_RATE_REQUEST;
            return true;
        }
        if(n == 34) {
            out = OPUS_GET_FINAL_RANGE_REQUEST;
            return true;
        }
        if(n == 35) {
            out = OPUS_GET_PITCH_REQUEST;
            return true;
        }
        if(n == 36) {
            out = OPUS_SET_GAIN_REQUEST;
            return true;
        }
        if(n == 37) {
            out = OPUS_GET_GAIN_REQUEST;
            return true;
        }
        if(n == 38) {
            out = OPUS_SET_LSB_DEPTH_REQUEST;
            return true;
        }
        if(n == 39) {
            out = OPUS_GET_LSB_DEPTH_REQUEST;
            return true;
        }
        if(n == 40) {
            out = OPUS_GET_LAST_PACKET_DURATION_REQUEST;
            return true;
        }
        if(n == 41) {
            out = OPUS_SET_EXPERT_FRAME_DURATION_REQUEST;
            return true;
        }
        if(n == 42) {
            out = OPUS_GET_EXPERT_FRAME_DURATION_REQUEST;
            return true;
        }
        if(n == 43) {
            out = OPUS_SET_PREDICTION_DISABLED_REQUEST;
            return true;
        }
        if(n == 44) {
            out = OPUS_GET_PREDICTION_DISABLED_REQUEST;
            return true;
        }
        if(n == 45) {
            out = OPUS_SET_PHASE_INVERSION_DISABLED_REQUEST;
            return true;
        }
        if(n == 46) {
            out = OPUS_GET_PHASE_INVERSION_DISABLED_REQUEST;
            return true;
        }
        if(n == 47) {
            out = OPUS_GET_IN_DTX_REQUEST;
            return true;
        }
        if(n == 52) {
            out = OPUS_AUTO;
            return true;
        }
        if(n == 53) {
            out = OPUS_BITRATE_MAX;
            return true;
        }
        if(n == 54) {
            out = OPUS_APPLICATION_VOIP;
            return true;
        }
        if(n == 55) {
            out = OPUS_APPLICATION_AUDIO;
            return true;
        }
        if(n == 56) {
            out = OPUS_APPLICATION_RESTRICTED_LOWDELAY;
            return true;
        }
        if(n == 57) {
            out = OPUS_SIGNAL_VOICE;
            return true;
        }
        if(n == 58) {
            out = OPUS_SIGNAL_MUSIC;
            return true;
        }
        if(n == 59) {
            out = OPUS_BANDWIDTH_NARROWBAND;
            return true;
        }
        if(n == 60) {
            out = OPUS_BANDWIDTH_MEDIUMBAND;
            return true;
        }
        if(n == 61) {
            out = OPUS_BANDWIDTH_WIDEBAND;
            return true;
        }
        if(n == 62) {
            out = OPUS_BANDWIDTH_SUPERWIDEBAND;
            return true;
        }
        if(n == 63) {
            out = OPUS_BANDWIDTH_FULLBAND;
            return true;
        }
        if(n == 64) {
            out = OPUS_FRAMESIZE_ARG;
            return true;
        }
        if(n == 65) {
            out = OPUS_FRAMESIZE_2_5_MS;
            return true;
        }
        if(n == 66) {
            out = OPUS_FRAMESIZE_5_MS;
            return true;
        }
        if(n == 67) {
            out = OPUS_FRAMESIZE_10_MS;
            return true;
        }
        if(n == 68) {
            out = OPUS_FRAMESIZE_20_MS;
            return true;
        }
        if(n == 69) {
            out = OPUS_FRAMESIZE_40_MS;
            return true;
        }
        if(n == 70) {
            out = OPUS_FRAMESIZE_60_MS;
            return true;
        }
        if(n == 71) {
            out = OPUS_FRAMESIZE_80_MS;
            return true;
        }
        if(n == 72) {
            out = OPUS_FRAMESIZE_100_MS;
            return true;
        }
        if(n == 73) {
            out = OPUS_FRAMESIZE_120_MS;
            return true;
        }
        if(n == 104) {
            out = OPUS_RESET_STATE;
            return true;
        }
        if(n == 115) {
            out = OPE_API_VERSION;
            return true;
        }
        if(n == 116) {
            out = OPE_OK;
            return true;
        }
        if(n == 117) {
            out = OPE_BAD_ARG;
            return true;
        }
        if(n == 118) {
            out = OPE_INTERNAL_ERROR;
            return true;
        }
        if(n == 119) {
            out = OPE_UNIMPLEMENTED;
            return true;
        }
        if(n == 120) {
            out = OPE_ALLOC_FAIL;
            return true;
        }
        if(n == 121) {
            out = OPE_CANNOT_OPEN;
            return true;
        }
        if(n == 122) {
            out = OPE_TOO_LATE;
            return true;
        }
        if(n == 123) {
            out = OPE_INVALID_PICTURE;
            return true;
        }
        if(n == 124) {
            out = OPE_INVALID_ICON;
            return true;
        }
        if(n == 125) {
            out = OPE_WRITE_FAIL;
            return true;
        }
        if(n == 126) {
            out = OPE_CLOSE_FAIL;
            return true;
        }
        if(n == 127) {
            out = OPE_SET_DECISION_DELAY_REQUEST;
            return true;
        }
        if(n == 128) {
            out = OPE_GET_DECISION_DELAY_REQUEST;
            return true;
        }
        if(n == 129) {
            out = OPE_SET_MUXING_DELAY_REQUEST;
            return true;
        }
        if(n == 130) {
            out = OPE_GET_MUXING_DELAY_REQUEST;
            return true;
        }
        if(n == 131) {
            out = OPE_SET_COMMENT_PADDING_REQUEST;
            return true;
        }
        if(n == 132) {
            out = OPE_GET_COMMENT_PADDING_REQUEST;
            return true;
        }
        if(n == 133) {
            out = OPE_SET_SERIALNO_REQUEST;
            return true;
        }
        if(n == 134) {
            out = OPE_GET_SERIALNO_REQUEST;
            return true;
        }
        if(n == 135) {
            out = OPE_SET_PACKET_CALLBACK_REQUEST;
            return true;
        }
        if(n == 136) {
            out = OPE_SET_HEADER_GAIN_REQUEST;
            return true;
        }
        if(n == 137) {
            out = OPE_GET_HEADER_GAIN_REQUEST;
            return true;
        }
        if(n == 138) {
            out = OPE_GET_NB_STREAMS_REQUEST;
            return true;
        }
        if(n == 139) {
            out = OPE_GET_NB_COUPLED_STREAMS_REQUEST;
            return true;
        }
        return false;
    }
}
namespace bindings {
    namespace opusenc {
        static NAN_METHOD(SetApplication) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v80;
            if(!Arguments::ConvertValue(info,0,v80)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_APPLICATION(v80));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetApplication) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v81;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_APPLICATION(&v81));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v81));
        }
        static NAN_METHOD(SetBitrate) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v82;
            if(!Arguments::ConvertValue(info,0,v82)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_BITRATE(v82));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetBitrate) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v83;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_BITRATE(&v83));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v83));
        }
        static NAN_METHOD(SetMaxBandwidth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v84;
            if(!Arguments::ConvertValue(info,0,v84)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_MAX_BANDWIDTH(v84));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetMaxBandwidth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v85;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_MAX_BANDWIDTH(&v85));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v85));
        }
        static NAN_METHOD(SetVbr) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v86;
            if(!Arguments::ConvertValue(info,0,v86)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_VBR(v86));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetVbr) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v87;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_VBR(&v87));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v87));
        }
        static NAN_METHOD(SetBandwidth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v88;
            if(!Arguments::ConvertValue(info,0,v88)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_BANDWIDTH(v88));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetBandwidth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v89;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_BANDWIDTH(&v89));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v89));
        }
        static NAN_METHOD(SetComplexity) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v90;
            if(!Arguments::ConvertValue(info,0,v90)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_COMPLEXITY(v90));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetComplexity) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v91;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_COMPLEXITY(&v91));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v91));
        }
        static NAN_METHOD(SetInbandFec) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v92;
            if(!Arguments::ConvertValue(info,0,v92)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_INBAND_FEC(v92));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetInbandFec) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v93;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_INBAND_FEC(&v93));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v93));
        }
        static NAN_METHOD(SetPacketLossPerc) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v94;
            if(!Arguments::ConvertValue(info,0,v94)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PACKET_LOSS_PERC(v94));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetPacketLossPerc) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v95;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PACKET_LOSS_PERC(&v95));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v95));
        }
        static NAN_METHOD(SetDtx) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v96;
            if(!Arguments::ConvertValue(info,0,v96)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_DTX(v96));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetDtx) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v97;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_DTX(&v97));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v97));
        }
        static NAN_METHOD(SetVbrConstraint) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v98;
            if(!Arguments::ConvertValue(info,0,v98)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_VBR_CONSTRAINT(v98));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetVbrConstraint) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v99;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_VBR_CONSTRAINT(&v99));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v99));
        }
        static NAN_METHOD(SetForceChannels) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v100;
            if(!Arguments::ConvertValue(info,0,v100)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_FORCE_CHANNELS(v100));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetForceChannels) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v101;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_FORCE_CHANNELS(&v101));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v101));
        }
        static NAN_METHOD(SetSignal) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v102;
            if(!Arguments::ConvertValue(info,0,v102)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_SIGNAL(v102));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetSignal) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v103;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_SIGNAL(&v103));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v103));
        }
        static NAN_METHOD(GetLookahead) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v104;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_LOOKAHEAD(&v104));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v104));
        }
        static NAN_METHOD(GetSampleRate) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v105;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_SAMPLE_RATE(&v105));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v105));
        }
        static NAN_METHOD(GetFinalRange) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_uint32 v106;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_FINAL_RANGE(&v106));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v106));
        }
        static NAN_METHOD(GetPitch) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v107;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PITCH(&v107));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v107));
        }
        static NAN_METHOD(SetGain) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v108;
            if(!Arguments::ConvertValue(info,0,v108)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_GAIN(v108));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetGain) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v109;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_GAIN(&v109));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v109));
        }
        static NAN_METHOD(SetLsbDepth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v110;
            if(!Arguments::ConvertValue(info,0,v110)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_LSB_DEPTH(v110));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetLsbDepth) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v111;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_LSB_DEPTH(&v111));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v111));
        }
        static NAN_METHOD(GetLastPacketDuration) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v112;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_LAST_PACKET_DURATION(&v112));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v112));
        }
        static NAN_METHOD(SetExpertFrameDuration) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v113;
            if(!Arguments::ConvertValue(info,0,v113)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_EXPERT_FRAME_DURATION(v113));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetExpertFrameDuration) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v114;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_EXPERT_FRAME_DURATION(&v114));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v114));
        }
        static NAN_METHOD(SetPredictionDisabled) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v115;
            if(!Arguments::ConvertValue(info,0,v115)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PREDICTION_DISABLED(v115));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetPredictionDisabled) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v116;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PREDICTION_DISABLED(&v116));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v116));
        }
        static NAN_METHOD(SetPhaseInversionDisabled) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v117;
            if(!Arguments::ConvertValue(info,0,v117)) {
                return;
            }
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_SET_PHASE_INVERSION_DISABLED(v117));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
        }
        static NAN_METHOD(GetPhaseInversionDisabled) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v118;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_PHASE_INVERSION_DISABLED(&v118));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v118));
        }
        static NAN_METHOD(GetInDtx) {
            Encoder* encoder;
            if(!Arguments::Unwrap<Encoder>(info.This(), encoder)) {
                return;
            }
            opus_int32 v119;
            encoder->error = ope_encoder_ctl(encoder->value,OPUS_GET_IN_DTX(&v119));
            if(encoder->error != OPE_OK) {
                Nan::ThrowError(Nan::New("Failed to call ope_encoder_ctl with error: " + std::string(ope_strerror(encoder->error))).ToLocalChecked());
                return;
            }
            info.GetReturnValue().Set(Nan::New(v119));
        }
        void SetEncoderGetterPrototypeMethods(v8::Local<v8::FunctionTemplate> tpl){
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
}
