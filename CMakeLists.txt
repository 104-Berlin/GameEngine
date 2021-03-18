cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_SYSTEM_VERSION 10.0)


set(BUILD_SHARED_LIBS TRUE)
add_subdirectory(deps/glfw)


find_package(OpenGL)

if (WIN32)
set(COMPILE_DEF ${COMPILE_DEF} EWIN)
elseif(APPLE)
set(COMPILE_DEF ${COMPILE_DEF} EMAC)
file(GLOB_RECURSE ENGINE_MAC_SRC_FILES src/*.mm)
else()
set(COMPILE_DEF ${COMPILE_DEF} EUNI)
endif()

set(COMPILE_DEF ${COMPILE_DEF} EEXPORT)

file(GLOB_RECURSE ENGINE_SRC_FILES  src/*.c
                                    src/*.cpp
                                    glad/src/glad.c
                                    deps/imgui/imgui.cpp
                                    deps/imgui/imgui_demo.cpp
                                    deps/imgui/imgui_draw.cpp
                                    deps/imgui/imgui_widgets.cpp
                                    deps/imgui/imgui_tables.cpp
                                    deps/imgui/backends/imgui_impl_glfw.cpp)


# Maybe just compile a single folder in wich all symbols are that the extensions need
add_library(Engine SHARED ${ENGINE_SRC_FILES}
                          ${ENGINE_MAC_SRC_FILES})



target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/ )

target_compile_definitions(Engine PUBLIC ${COMPILE_DEF}) 
                                        
target_link_libraries(Engine glfw)

if (APPLE)
    find_library(OpenGL_LIBRARY OpenGL )
    find_library(COCOA_LIBRARY Cocoa)

    target_link_libraries(Engine ${OpenGL_LIBRARY})
    target_link_libraries(Engine ${COCOA_LIBRARY})
elseif(WIN32)
    target_link_libraries(Engine Rpcrt4.lib)
    target_link_libraries(Engine opengl32)
    target_link_libraries(Engine gdi32)
endif(APPLE)


add_executable(EngineRun main.cpp)
target_link_libraries(EngineRun Engine)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Open_Sans/OpenSans-SemiBold.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Engine/)