cmake_minimum_required(VERSION 3.15)
project(CSV)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSV main.cpp CSVParser.h)