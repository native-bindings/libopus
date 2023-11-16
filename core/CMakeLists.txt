get_filename_component(CURRENT_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

if(NOT DEFINED CMAKE_JS_VERSION)
    set(CMAKE_JS_INC
        ${CURRENT_DIR_PATH}/node_modules/nan
        $ENV{NVM_INC}
    )
endif()

add_library(
    NodeNativeBindingsCore SHARED
    ${CMAKE_JS_SRC}
    Arguments.cpp Arguments.h
)
target_link_libraries(
    NodeNativeBindingsCore
    PUBLIC ${CMAKE_JS_LIB}
)
target_include_directories(
    NodeNativeBindingsCore
    PUBLIC ${CMAKE_JS_INC} ${CURRENT_DIR_PATH}
)