cmake_minimum_required(VERSION 3.15)
project(ExAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src       ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/glfw/include
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/assimp/include
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../glad/include
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/glm/glm
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/json/single_include
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imgui
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imguizmo
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/entt/single_include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/)
set(CMAKE_SHARED_LIBRARY_SUFFIX .epl)

add_library(Animation SHARED entry.cpp)


if (WIN32)
target_link_libraries(Animation ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libsEngined.lib)
elseif(APPLE)
target_link_libraries(Animation ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libsEngined.a)
endif()


SET_TARGET_PROPERTIES(Animation PROPERTIES PREFIX "")