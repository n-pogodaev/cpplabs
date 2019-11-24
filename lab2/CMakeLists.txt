cmake_minimum_required(VERSION 3.15)
project(WorkflowExecutor)

set(CMAKE_CXX_STANDARD 14)

add_executable(WorkflowExecutor main.cpp Worker.h Readfile.cpp Readfile.h Writefile.cpp Writefile.h Grep.cpp Grep.h Sort.cpp Sort.h Replace.cpp Replace.h Dump.cpp Dump.h Parser.cpp Parser.h Executor.cpp Executor.h IOWorker.h IOWorker.cpp AllWorkers.h)
