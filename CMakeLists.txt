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

add_executable(Engine   ${ENGINE_SRC_FILES}
                        main.cpp )

# Maybe just compile a single folder in wich all symbols are that the extensions need
add_library(sEngine     ${ENGINE_SRC_FILES})

target_link_libraries(Engine ${EXTRA_LIBS})
target_link_libraries(Engine glfw)
target_link_libraries(Engine assimp)

target_link_libraries(sEngine ${EXTRA_LIBS})
target_link_libraries(sEngine glfw)
target_link_libraries(sEngine assimp)

if (WIN32)
target_link_libraries(Engine opengl32)
target_link_libraries(Engine gdi32)

target_link_libraries(sEngine opengl32)
target_link_libraries(sEngine gdi32)
endif(WIN32)
