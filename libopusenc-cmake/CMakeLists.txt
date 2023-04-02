project(opusenc C)

set(SRC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    libopusenc STATIC
    ${SRC_FOLDER}/src/opusenc.c
    ${SRC_FOLDER}/src/opus_header.c
    ${SRC_FOLDER}/src/ogg_packer.c
    ${SRC_FOLDER}/src/resample.c
    ${SRC_FOLDER}/src/picture.c
    ${SRC_FOLDER}/src/unicode_support.c

)
target_include_directories(libopusenc PUBLIC ${SRC_FOLDER}/include ${SRC_FOLDER}/src)
target_link_libraries(libopusenc PUBLIC opus PRIVATE speexdsp)
target_compile_definitions(
    libopusenc PRIVATE
    PACKAGE_VERSION="0.0.1" PACKAGE_NAME="opusenc" HAVE_CONFIG_H
    OUTSIDE_SPEEX RANDOM_PREFIX=NodeOpusEnc
)

configure_file(${SRC_FOLDER}/include/config.h.in ${SRC_FOLDER}/include/config.h)