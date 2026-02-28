cmake_minimum_required(VERSION 3.10)
project(Search VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(search
    src/main.cc
    src/logs.cc
    src/include/utilities.h
)
