cmake_minimum_required(VERSION 3.15)
project(ExAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

include_directories()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/)
set(CMAKE_SHARED_LIBRARY_SUFFIX .epl)

add_library(Animation SHARED entry.cpp)