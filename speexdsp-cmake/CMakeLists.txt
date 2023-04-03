project(speexdsp C)


set(SRC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    speexdsp STATIC
    ${SRC_FOLDER}/libspeexdsp/buffer.c
    ${SRC_FOLDER}/libspeexdsp/jitter.c
    ${SRC_FOLDER}/libspeexdsp/smallft.c
    ${SRC_FOLDER}/libspeexdsp/scal.c
    ${SRC_FOLDER}/libspeexdsp/kiss_fftr.c
    ${SRC_FOLDER}/libspeexdsp/fftwrap.c
    ${SRC_FOLDER}/libspeexdsp/resample.c
    ${SRC_FOLDER}/libspeexdsp/filterbank.c
    ${SRC_FOLDER}/libspeexdsp/mdf.c
    ${SRC_FOLDER}/libspeexdsp/kiss_fft.c
    ${SRC_FOLDER}/libspeexdsp/preprocess.c
    ${SRC_FOLDER}/libspeexdsp/testresample2.c
    ${SRC_FOLDER}/libspeexdsp/kiss_fftr.h
    ${SRC_FOLDER}/libspeexdsp/smallft.h
    ${SRC_FOLDER}/libspeexdsp/misc_bfin.h
    ${SRC_FOLDER}/libspeexdsp/_kiss_fft_guts.h
    ${SRC_FOLDER}/libspeexdsp/resample_sse.h
    ${SRC_FOLDER}/libspeexdsp/fixed_bfin.h
    ${SRC_FOLDER}/libspeexdsp/filterbank.h
    ${SRC_FOLDER}/libspeexdsp/fixed_generic.h
    ${SRC_FOLDER}/libspeexdsp/fixed_debug.h
    ${SRC_FOLDER}/libspeexdsp/fixed_arm4.h
    ${SRC_FOLDER}/libspeexdsp/math_approx.h
    ${SRC_FOLDER}/libspeexdsp/bfin.h
    ${SRC_FOLDER}/libspeexdsp/pseudofloat.h
    ${SRC_FOLDER}/libspeexdsp/resample_neon.h
    ${SRC_FOLDER}/libspeexdsp/vorbis_psy.h
    ${SRC_FOLDER}/libspeexdsp/kiss_fft.h
    ${SRC_FOLDER}/libspeexdsp/fixed_arm5e.h
    ${SRC_FOLDER}/libspeexdsp/fftwrap.h
    ${SRC_FOLDER}/libspeexdsp/os_support.h
    ${SRC_FOLDER}/libspeexdsp/arch.h
)
target_include_directories(speexdsp PUBLIC ${SRC_FOLDER}/include/speex libspeexdsp PRIVATE ${SRC_FOLDER}/include)
target_compile_definitions(speexdsp PUBLIC HAVE_CONFIG_H)

set(INCLUDE_STDINT "#include <stdint.h>")
set(SIZE16 "int16_t")
set(USIZE16 "uint16_t")
set(SIZE32 "int32_t")
set(USIZE32 "uint32_t")
configure_file(
    ${SRC_FOLDER}/include/speex/speexdsp_config_types.h.in
    ${SRC_FOLDER}/include/speex/speexdsp_config_types.h
)

set(FLOATING_POINT 1)
set(USE_SMALLFT 1)
set(EXPORT "__attribute__((visibility(\"default\")))")
configure_file(speexdsp.config.h.in ${SRC_FOLDER}/include/config.h)
