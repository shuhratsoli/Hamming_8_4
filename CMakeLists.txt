cmake_minimum_required(VERSION 3.10)

project(Hamming_8_4)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(Hamming Hamming_8_4.cpp)

add_executable(hamming_8_4 main.cpp)

target_link_libraries(hamming_8_4 PRIVATE Hamming)
