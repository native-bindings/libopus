add_library(
    NodeOpusEnc SHARED
    opusenc.cpp opusenc.h Encoder.cpp Encoder.h Comments.cpp Comments.h
    EncoderBase.h EncoderBase.cpp
)
target_link_libraries(NodeOpusEnc PRIVATE NodeNativeBindingsCore Opus libopusenc)
