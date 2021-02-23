cmake_minimum_required(VERSION 3.15)
project(Tischler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/)

if (WIN32)
	add_compile_definitions(EWIN)
	
	set(EXTRA_LIBS ${EXTRA_LIBS} Rpcrt4.lib)
elseif(APPLE)
	add_compile_definitions(EMAC)
	include_directories( /System/Library/Frameworks )
	find_library(OpenGL_LIBRARY OpenGL )
	find_library(COCOA_LIBRARY Cocoa)
	set(EXTRA_LIBS ${OpenGL_LIBRARY} ${COCOA_LIBRARY})
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/)
set(CMAKE_SHARED_LIBRARY_SUFFIX .epl)

add_library(Tischler MODULE entry.cpp)
target_link_libraries(Tischler ${EXTRA_LIBS})

if (WIN32)
target_link_libraries(Tischler ${CMAKE_CURRENT_SOURCE_DIR}/../../Debug/Engine.lib)
else()
target_link_libraries(Tischler ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libEngine.dylib)
endif(WIN32)