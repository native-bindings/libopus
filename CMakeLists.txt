cmake_minimum_required(VERSION 3.0)
project(opusenc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(-Wfatal-errors)

if(CMAKE_JS_VERSION)
    set(
        NODE_ADDON_INCLUDE_DIRECTORIES
        ${NODE_ADDON_INCLUDE_DIRECTORIES}
        ${CMAKE_JS_INC}
    )
else()
    set(
        NODE_ADDON_INCLUDE_DIRECTORIES
        ${NODE_ADDON_INCLUDE_DIRECTORIES}
        $ENV{NVM_INC} ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan
    )
endif()

add_library(node_addon INTERFACE)
set_target_properties(
    node_addon PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${NODE_ADDON_INCLUDE_DIRECTORIES}"
)

add_subdirectory(speexdsp-cmake)
add_subdirectory(libopusenc-cmake)
add_subdirectory(opus)
add_subdirectory(opusfile)
add_subdirectory(src)
