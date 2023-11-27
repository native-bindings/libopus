cmake_minimum_required(VERSION 3.0)
project(opusenc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wfatal-errors)

add_subdirectory(core)
add_subdirectory(libs)
add_subdirectory(src)
