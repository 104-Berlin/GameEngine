cmake_minimum_required(VERSION 3.15)
project(Tischler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/)

if (WIN32)
	add_compile_definitions(EWIN)
elseif(APPLE)
	add_compile_definitions(EMAC)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/)
set(CMAKE_SHARED_LIBRARY_SUFFIX .epl)

add_library(Tischler MODULE entry.cpp)
