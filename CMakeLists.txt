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
    NodeOpusEnc SHARED
    ${CMAKE_JS_SRC}
    main.cpp Encoder.cpp Encoder.h Comments.cpp Comments.h Arguments.cpp Arguments.h
    Constants.cpp
)
target_include_directories(
    NodeOpusEnc PRIVATE
    ${NODE_INSTALL_DIR}/include/node
    ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan
    ${CMAKE_JS_INC}
)
target_link_libraries(NodeOpusEnc PRIVATE libopusenc ${CMAKE_JS_LIB})

if (CMAKE_JS_VERSION)
set_target_properties(NodeOpusEnc PROPERTIES PREFIX "" SUFFIX ".node")
endif()
