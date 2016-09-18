cmake_minimum_required(VERSION 3.5)
project(parsing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp parsing.cpp parsing.h)
add_executable(parsing ${SOURCE_FILES})