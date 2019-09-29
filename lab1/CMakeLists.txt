cmake_minimum_required(VERSION 3.14)
project(RNA)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Google_tests)
add_executable(RNA main.cpp RNA.cpp RNA.h)
