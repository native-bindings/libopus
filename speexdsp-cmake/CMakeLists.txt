cmake_minimum_required(VERSION 3.0)
project(speexdsp C)

add_subdirectory(config)

set(SRC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src/libspeexdsp)

add_library(
    speexdsp STATIC
    ${SRC_FOLDER}/buffer.c ${SRC_FOLDER}/jitter.c ${SRC_FOLDER}/smallft.c ${SRC_FOLDER}/scal.c
    ${SRC_FOLDER}/kiss_fftr.c ${SRC_FOLDER}/fftwrap.c ${SRC_FOLDER}/resample.c ${SRC_FOLDER}/filterbank.c
    ${SRC_FOLDER}/mdf.c ${SRC_FOLDER}/kiss_fft.c ${SRC_FOLDER}/preprocess.c ${SRC_FOLDER}/testresample2.c
    ${SRC_FOLDER}/kiss_fftr.h ${SRC_FOLDER}/smallft.h ${SRC_FOLDER}/misc_bfin.h ${SRC_FOLDER}/_kiss_fft_guts.h
    ${SRC_FOLDER}/resample_sse.h ${SRC_FOLDER}/fixed_bfin.h ${SRC_FOLDER}/filterbank.h
    ${SRC_FOLDER}/fixed_generic.h ${SRC_FOLDER}/fixed_debug.h ${SRC_FOLDER}/fixed_arm4.h
    ${SRC_FOLDER}/math_approx.h ${SRC_FOLDER}/bfin.h ${SRC_FOLDER}/pseudofloat.h
    ${SRC_FOLDER}/resample_neon.h ${SRC_FOLDER}/vorbis_psy.h ${SRC_FOLDER}/kiss_fft.h
    ${SRC_FOLDER}/fixed_arm5e.h ${SRC_FOLDER}/fftwrap.h ${SRC_FOLDER}/os_support.h ${SRC_FOLDER}/arch.h
)
target_compile_definitions(speexdsp PUBLIC HAVE_CONFIG_H)
target_link_libraries(speexdsp PRIVATE speexdsp_config)
target_include_directories(speexdsp PRIVATE src/include)
