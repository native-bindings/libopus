project(opusenc CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(-Wfatal-errors)

add_subdirectory(speexdsp-cmake)
add_subdirectory(libopusenc-cmake)
add_subdirectory(opus)

add_library(
    NodeOpus SHARED
    ${CMAKE_JS_SRC}
    src/Encoder.h src/Encoder.cpp src/opusenc/opusenc.cpp src/opusenc/opusenc.h
    main.cpp src/opusenc/Encoder.cpp src/opusenc/Encoder.h src/opusenc/Comments.cpp src/opusenc/Comments.h
    src/Arguments.cpp src/Arguments.h src/Constants.cpp src/Constants.h src/Decoder.cpp src/Decoder.h
)
target_include_directories(
    NodeOpus PRIVATE
    ${NODE_INSTALL_DIR}/include/node
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan
    ${CMAKE_JS_INC}
)
target_link_libraries(NodeOpus PRIVATE libopusenc ${CMAKE_JS_LIB})

if (CMAKE_JS_VERSION)
set_target_properties(NodeOpus PROPERTIES PREFIX "" SUFFIX ".node")
endif()
