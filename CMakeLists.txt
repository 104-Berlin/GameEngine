cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -std=c++14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)



include_directories(Infinit/src     deps/glfw/include
                                    glad/include
                                    deps/glm/glm
                                    ./include )


add_subdirectory(deps/glfw)
find_package(OpenGL)


if (WIN32)


endif(WIN32)

if (APPLE)
INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(METAL_LIBRARY MetalKit)
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
SET(EXTRA_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY} ${METAL_LIBRARY})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
  -framework AppKit \
  -framework Metal \
  -framework MetalKit \
  -framework ModelIO \
  -framework QuartzCore" )
endif(APPLE)


add_executable(Engine  
                        glad/src/glad.c
                        src/platform/opengl/engine_opengl_buffer.cpp
                        src/platform/opengl/engine_opengl_render_context.cpp
                        src/platform/opengl/engine_opengl_shader.cpp
                        src/platform/opengl/engine_opengl_texture.cpp
                        src/graphics/engine_buffer.cpp
                        src/graphics/engine_camera.cpp
                        src/graphics/engine_frame_buffer.cpp
                        src/graphics/engine_render_command_queue.cpp
                        src/graphics/engine_render_context.cpp
                        src/graphics/engine_renderer.cpp
                        src/graphics/engine_shader.cpp
                        src/graphics/engine_texture.cpp
                        src/graphics/engine_vertex_array.cpp
                        src/graphics/engine_window.cpp
                        main.cpp )

target_link_libraries(Engine ${EXTRA_LIBS})
target_link_libraries(Engine glfw)

if (WIN32)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine gdi32)
endif(WIN32)
