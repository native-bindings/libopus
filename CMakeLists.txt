cmake_minimum_required(VERSION 3.0)
project(opusenc CXX)

set(OP_DISABLE_HTTP true)
set(OP_DISABLE_EXAMPLES true)
set(OP_DISABLE_DOCS true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(-Wfatal-errors)

if(DEFINED CMAKE_JS_VERSION)
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
target_include_directories(node_addon INTERFACE ${NODE_ADDON_INCLUDE_DIRECTORIES})
target_link_libraries(node_addon INTERFACE ${CMAKE_JS_LIB})

add_subdirectory(ogg)
add_subdirectory(opus)
add_subdirectory(opusfile)
add_subdirectory(speexdsp-cmake)
add_subdirectory(libopusenc-cmake)
add_subdirectory(src)
