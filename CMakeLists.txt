cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(Infinit/src     deps/glfw/include
                                    deps/assimp/include
                                    glad/include
                                    deps/glm/glm
                                    deps/json/single_include
                                    deps/imgui
                                    deps/imguizmo
                                    deps/entt/single_include
                                    ./src )


add_subdirectory(deps/glfw)


set(ZLIB_LIBRARIES zlibstatic)
set(ASSIMP_BUILD_TESTS OFF)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
add_subdirectory(deps/assimp)


find_package(OpenGL)

if (WIN32)
add_compile_definitions(EWIN)
elseif(APPLE)
add_compile_definitions(EMAC)
endif()

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
                        deps/imgui/imgui.cpp
                        deps/imgui/imgui_demo.cpp
                        deps/imgui/imgui_draw.cpp
                        deps/imgui/imgui_widgets.cpp
                        deps/imgui/imgui_tables.cpp
                        deps/imgui/backends/imgui_impl_glfw.cpp
                        deps/imgui/backends/imgui_impl_opengl3.cpp
                        src/util/engine_timer.cpp
                        src/file/engine_file.cpp
                        src/file/engine_folder.cpp
                        src/platform/opengl/engine_opengl_buffer.cpp
                        src/platform/opengl/engine_opengl_render_context.cpp
                        src/platform/opengl/engine_opengl_shader.cpp
                        src/platform/opengl/engine_opengl_texture.cpp
                        src/graphics/engine_buffer.cpp
                        src/graphics/engine_camera.cpp
                        src/graphics/engine_render_command_queue.cpp
                        src/graphics/engine_render_context.cpp
                        src/graphics/engine_renderer.cpp
                        src/graphics/engine_shader.cpp
                        src/graphics/engine_texture.cpp
                        src/graphics/engine_window.cpp
                        src/properties/engine_json_converter.cpp
                        src/properties/engine_property.cpp
                        src/scene/engine_uuid.cpp
                        src/scene/object/engine_object.cpp
                        src/scene/engine_scene.cpp
                        src/component/engine_component.cpp
                        src/resource/engine_resource.cpp
                        src/resource/engine_resource_manager.cpp
                        src/resource/engine_mesh.cpp
                        src/resource/engine_sprite.cpp
                        src/ui/engine_ui.cpp
                        src/ui/engine_input_field.cpp
                        src/core/engine_application.cpp
                        src/extensions/engine_extension_manager.cpp
                        main.cpp )

target_link_libraries(Engine ${EXTRA_LIBS})
target_link_libraries(Engine glfw)
target_link_libraries(Engine assimp)

if (WIN32)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine gdi32)
endif(WIN32)
