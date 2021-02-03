cmake_minimum_required(VERSION 3.15)
project(ExAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

if (WIN32)
add_compile_definitions(EWIN)
elseif(APPLE)
add_compile_definitions(EMAC)
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)
include_directories ( /System/Library/Frameworks )


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/)
set(CMAKE_SHARED_LIBRARY_SUFFIX .epl)

add_library(Animation SHARED entry.cpp)



if (WIN32)
target_link_libraries(Animation ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libEngine.lib)
elseif(APPLE)
#target_link_libraries(Animation ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libEngine.a)
target_link_libraries(Animation "-framework CoreFoundation")
target_link_options(Animation PRIVATE -undefined dynamic_lookup)
endif()


SET_TARGET_PROPERTIES(Animation PROPERTIES PREFIX "")