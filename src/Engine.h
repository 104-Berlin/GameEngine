#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <stdarg.h>
#include <memory>
#include <filesystem>
#include <queue>
#include <thread>


#ifdef EWIN
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;
typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;
typedef uint_fast8_t byte;

typedef std::string EString;


template <typename T>
using EVector = std::vector<T>;

template <typename K, typename V>
using EMap = std::map<K, V>;

template <typename K, typename V>
using EUnorderedMap = std::unordered_map<K, V>;


template <typename T>
using EScope = std::unique_ptr<T>;
#define EMakeScope(Type, ...) std::make_unique<Type>(__VA_ARGS__)


template <typename T>
using ERef = std::shared_ptr<T>;
#define EMakeRef(Type, ...) std::make_shared<Type>(__VA_ARGS__)

template <typename T>
using EWeakRef = std::weak_ptr<T>;

const char kPathSeparator =
#ifdef EWIN
                            '\\';
#else
                            '/';
#endif


//------------------------------------------------------------------
// Extern Dependencies


#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/quaternion.hpp>

#include <nlohmann/json.hpp>

#include <imgui.h>
#include <ImGuizmo.h>
#include <entt/entt.hpp>


// Entities are saved in a registry and can have components attached to
typedef entt::entity    EEntity;

typedef glm::vec2       EVec2;
typedef glm::vec3       EVec3;
typedef glm::vec4       EVec4;
typedef glm::mat4       EMat4;

typedef EVec4           EColor;
typedef nlohmann::json  EJson;



// ------------------------------------------------------------------ 

#include "predefined_classes.h"

#include "util/engine_timer.h"

#include "file/engine_file.h"
#include "file/engine_folder.h"




#include "scene/engine_uuid.h"
#include "resource/engine_resource.h"
#include "resource/engine_resource_loader.h"
#include "resource/engine_resource_manager.h"
#include "properties/engine_json_converter.h"


#include "properties/engine_property.h"


#include "graphics/engine_window.h"
#include "graphics/engine_light.h"
#include "graphics/engine_camera.h"
#include "graphics/engine_render_context.h"
#include "graphics/engine_render_command_queue.h"
#include "graphics/engine_buffer.h"
#include "graphics/engine_shader_uniforms.h"
#include "graphics/engine_shader.h"
#include "graphics/engine_texture.h"
#include "graphics/engine_renderer.h"



#include "platform/opengl/engine_opengl_render_context.h"
#include "platform/opengl/engine_opengl_buffer.h"
#include "platform/opengl/engine_opengl_shader.h"
#include "platform/opengl/engine_opengl_texture.h"

#include "resource/engine_mesh.h"
#include "resource/engine_sprite.h"


#include "extensions/engine_extension_manager.h"


#include "component/engine_component.h"
#include "scene/engine_scene.h"

#include "scene/object/engine_object.h"



#include "ui/engine_ui.h"
#include "ui/engine_input_field.h"

#include "core/engine_application.h"
