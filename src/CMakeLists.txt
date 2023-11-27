add_subdirectory(opusenc)
add_subdirectory(opusfile)

add_library(
    NodeOpus SHARED
    Encoder.h Encoder.cpp main.cpp Constants.cpp Constants.h
    Decoder.cpp Decoder.h EncoderBase.cpp EncoderBase.h
    DecoderBase.cpp DecoderBase.h
)
target_link_libraries(NodeOpus PRIVATE opusfile libopusenc NodeNativeBindingsCore Opus NodeOpusFile NodeOpusEnc)

if (CMAKE_JS_VERSION)
    set_target_properties(
        NodeOpus PROPERTIES
        PREFIX "" SUFFIX ".node"
    )
endif()
