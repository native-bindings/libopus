add_library(
    NodeOpusFile SHARED OpusFile.cpp OpusFile.h
)
target_link_libraries(NodeOpusFile PRIVATE NodeNativeBindingsCore Opus opusfile)
