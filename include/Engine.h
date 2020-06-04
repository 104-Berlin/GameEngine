#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>

typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;
typedef uint_fast8_t byte;

typedef std::string EString;

template <typename T>
using EVector = std::vector<T>;


//------------------------------------------------------------------
// Extern Dependencies

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm.hpp>


// ------------------------------------------------------------------
 ///// TEMP
class Resource
{
protected:
EString fName;
EString fFilePath;
public:
Resource(const EString& name, const EString& filepath)
    : fName(name), fFilePath(filepath)
    {}

    void SetName(const EString& name) { fName = name; }
    const EString& GetName() const { return fName; }

    const EString& GetFilePath() const { return fFilePath; }
};

// ------------------------------------------------------------------ 

#include "graphics/engine_window.h"
#include "graphics/engine_light.h"
#include "graphics/engine_camera.h"
#include "graphics/engine_render_context.h"
#include "graphics/engine_render_command_queue.h"
#include "graphics/engine_renderer.h"
#include "graphics/engine_buffer.h"
#include "graphics/engine_shader_uniforms.h"
#include "graphics/engine_shader.h"
#include "graphics/engine_vertex_array.h"
#include "graphics/engine_frame_buffer.h"
#include "graphics/engine_texture.h"



#include "platform/opengl/engine_opengl_render_context.h"
#include "platform/opengl/engine_opengl_buffer.h"
#include "platform/opengl/engine_opengl_shader.h"
#include "platform/opengl/engine_opengl_texture.h"