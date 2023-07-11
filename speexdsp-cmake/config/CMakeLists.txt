cmake_minimum_required(VERSION 3.0)
project(speexdsp_config)

# preset some variables
set(CONFIG_FILE_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/speexdsp)

# project options
option(SPEEXDSP_FFT "FFT algorithm of choice" "smallft")
option(FIXED_POINT "Use fixed-point integers" false)

# create config.h file

# FFT
if(SPEEXDSP_FFT STREQUAL "gpl-fftw3")
    set(USE_GPL_FFTW3 1)
    # include the package into speexdsp
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(FFT3F fftw3f REQUIRED)
        set(LIBRARIES ${LIBRARIES} fftw3f)
    else()
        # try other way to get the module
    endif()
elseif(SPEEXDSP_FFT STREQUAL "kiss")
    set(USE_KISS_FFT 1)
elseif(SPEEXDSP_FFT STREQUAL "proprietary-intel-mkl")
    set(USE_INTEL_MKL 1)
    check_c_source_compiles(C "
        #include <mkl.h>
        void func() {
            DFTI_DESCRIPTOR_HANDLE h;
            MKL_LONG result=DftiCreateDescriptor(&h, DFTI_SINGLE, DFTI_REAL, 0);
        }
    ")
else(SPEEXDSP_FFT STREQUAL "smallft")
    set(USE_SMALLFT 1)
endif()

# FIXED_POINT
if(FIXED_POINT)
    set(FLOATING_POINT 0)
else()
    set(FLOATING_POINT 1)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CONFIG_FILE_DESTINATION}/config.h
)

# create the library

set(DEFINITIONS "${DEFINITIONS} EXPORT=__attribute__((visibility(\"default\")))")

add_library(speexdsp_config INTERFACE)
set_target_properties(
    speexdsp_config PROPERTIES
    INTERFACE_COMPILE_DEFINITIONS "${DEFINITIONS}"
    INTERFACE_INCLUDE_DIRECTORIES ${CONFIG_FILE_DESTINATION}
)

# create speexdsp_config_types.h file

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(inttypes.h HAVE_INT_TYPES_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)

if(HAVE_STDINT_H)
    set(INCLUDE_STDINT "#include <stdint.h>")
elseif(HAVE_INT_TYPES_H)
    set(INCLUDE_STDINT "#include <inttypes.h>")
elesif(HAVE_SYS_TYPES_H)
    set(INCLUDE_STDINT "#include <sys/types.h>")
else()
    message(FATAL_ERROR "Could not find content for INCLUDE_STDINT")
endif()

include(CheckTypeSize)
check_type_size(int16_t HAVE_INT16)
check_type_size(uint16_t HAVE_UINT16)
check_type_size(int32_t HAVE_INT32)
check_type_size(uint32_t HAVE_UINT32)

if(HAVE_INT16)
    set(SIZE16 int16_t)
endif()

if(HAVE_UINT16)
    set(USIZE16 uint16_t)
endif()

if(HAVE_INT32)
    set(SIZE32 int32_t)
endif()

if(HAVE_UINT32)
    set(USIZE32 uint32_t)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include/speex/speexdsp_config_types.h.in
    ${CONFIG_FILE_DESTINATION}/speexdsp_config_types.h
)

