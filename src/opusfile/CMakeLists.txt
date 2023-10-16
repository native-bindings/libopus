cmake_minimum_required(VERSION 3.0)
project(NodeOpusFile CXX)

add_library(
    NodeOpusFile SHARED OpusFile.cpp OpusFile.h
)
target_link_libraries(NodeOpusFile PRIVATE node_addon opusfile)