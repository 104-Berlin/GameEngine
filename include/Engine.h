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
#include <entt/entt.hpp>


typedef glm::vec2       EVec2;
typedef glm::vec3       EVec3;
typedef glm::vec4       EVec4;
typedef glm::mat4       EMat4;

typedef EVec4           EColor;
typedef nlohmann::json  EJson;



// ------------------------------------------------------------------
///// TEMP
class Resource
{
protected:
EString fName;
EString fFilePath;
public:
Resource(const EString& name, const EString& filepath = "")
    : fName(name), fFilePath(filepath)
    {}

    bool Reload(const EString& filepath = "")
    {
        if (!filepath.empty() && fFilePath.compare(filepath) != 0)
        {
            fFilePath = filepath;
        }
        if (!fFilePath.empty())
        {
            return OnReload();
        }
        return false;
    }

    virtual bool OnReload() = 0;


    void SetName(const EString& name) { fName = name; }
    const EString& GetName() const { return fName; }

    const EString& GetFilePath() const { return fFilePath; }
};

// ------------------------------------------------------------------ 

#include "predefined_classes.h"

#include "util/engine_timer.h"

#include "file/engine_file.h"
#include "file/engine_folder.h"




#include "scene/engine_uuid.h"
#include "properties/engine_json_converter.h"


#include "scene/object/engine_object.h"
#include "resource/engine_resource.h"



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


#include "component/engine_component.h"
#include "component/engine_mesh_component.h"
#include "component/engine_sprite_component.h"
#include "scene/engine_scene.h"


#include "ui/engine_ui.h"
#include "ui/engine_input_field.h"

#include "core/engine_application.h"
