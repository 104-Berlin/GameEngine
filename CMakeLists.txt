cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(deps/glfw/include
                    deps/imgui
                    glad/include
                    ./src )


add_subdirectory(deps/glfw)


find_package(OpenGL)

if (WIN32)
add_compile_definitions(EWIN)
elseif(APPLE)
add_compile_definitions(EMAC)
endif()

if (APPLE)
include_directories( /System/Library/Frameworks )
find_library(OpenGL_LIBRARY OpenGL )
find_library(COCOA_LIBRARY Cocoa)
set(EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY} ${COCOA_LIBRARY})
elseif(WIN32)
set(EXTRA_LIBS ${EXTRA_LIBS} Rpcrt4.lib)
endif(APPLE)

file(GLOB_RECURSE ENGINE_SRC_FILES  src/*.c
                                    src/*.cpp
                                    glad/src/glad.c
                                    deps/imgui/imgui.cpp
                                    deps/imgui/imgui_demo.cpp
                                    deps/imgui/imgui_draw.cpp
                                    deps/imgui/imgui_widgets.cpp
                                    deps/imgui/imgui_tables.cpp
                                    deps/imgui/backends/imgui_impl_glfw.cpp
                                    deps/imgui/backends/imgui_impl_opengl3.cpp)


# Maybe just compile a single folder in wich all symbols are that the extensions need
add_library(Engine     ${ENGINE_SRC_FILES})

target_link_libraries(Engine ${EXTRA_LIBS})
target_link_libraries(Engine glfw)
target_compile_definitions(Engine PUBLIC NAP_SHARED_LIBRARY NAP_SHARED_LIBRARY_IMGUI)

if (WIN32)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine gdi32)

set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif(WIN32)


add_executable(EngineRun main.cpp)
target_link_libraries(EngineRun Engine)

if (WIN32)
set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif(WIN32)