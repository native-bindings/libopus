cmake_minimum_required(VERSION 3.0)
project(NodeOpusEnc CXX)

add_library(
    NodeOpusEnc SHARED
    opusenc.cpp opusenc.h Encoder.cpp Encoder.h Comments.cpp Comments.h
)
target_link_libraries(NodeOpusEnc PRIVATE node_addon opus libopusenc)