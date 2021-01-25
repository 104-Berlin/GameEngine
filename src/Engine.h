#pragma once

#include "std_include.h"


//------------------------------------------------------------------
// Extern Dependencies


#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>




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
#include "graphics/engine_ui_renderer.h"




#include "platform/opengl/engine_opengl_render_context.h"
#include "platform/opengl/engine_opengl_buffer.h"
#include "platform/opengl/engine_opengl_shader.h"
#include "platform/opengl/engine_opengl_texture.h"

#include "resource/engine_mesh.h"
#include "resource/engine_sprite.h"




#include "component/engine_component.h"
#include "scene/engine_scene.h"
#include "scene/object/engine_object.h"





#include "ui/engine_ui.h"
#include "ui/engine_ui_functions.h"
#include "ui/engine_ui_fields.h"
#include "ui/engine_panels.h"


#include "extensions/engine_extension_manager.h"

#include "core/engine_application.h"
