cmake_minimum_required(VERSION 3.0)
project(NodeOpus CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(opusenc)
add_subdirectory(opusfile)

add_library(
    NodeOpus SHARED
    ${CMAKE_JS_SRC}
    Encoder.h Encoder.cpp main.cpp Arguments.cpp Arguments.h
    Constants.cpp Constants.h Decoder.cpp Decoder.h
    EncoderGettersAndSetters.cpp
)
target_link_libraries(NodeOpus PRIVATE opusfile libopusenc node_addon opus NodeOpusFile NodeOpusEnc)

if (CMAKE_JS_VERSION)
    set_target_properties(
        NodeOpus PROPERTIES
        PREFIX "" SUFFIX ".node"
    )
endif()
