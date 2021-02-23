#include "../std_include.h"

namespace Engine {
    class EObject;
}

#include "../event/engine_event_dispatcher.h"
#include "../scene/engine_uuid.h"
#include "../file/engine_folder.h"
#include "../file/engine_file.h"

#include "../properties/engine_json_converter.h"
#include "../properties/engine_property.h"
#include "../scene/engine_scene.h"
#include "../scene/object/engine_object.h"

#include "../resource/engine_resource.h"

#include "../graphics/engine_light.h"
#include "../graphics/engine_shader.h"
#include "../graphics/engine_camera.h"
#include "../graphics/engine_texture.h"
#include "../graphics/engine_buffer.h"
#include "../graphics/engine_render_command_queue.h"
#include "../graphics/engine_renderer.h"

#include "../resource/engine_mesh.h"
#include "../resource/engine_resource_manager.h"

#include "../ui/engine_ui_fields.h"
#include "../ui/engine_ui_functions.h"
#include "../ui/engine_ui_manager.h"

#include "../ui/engine_panels.h"
#include "engine_extension_manager.h"

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#ifdef EWIN
#define EXPORT_API EXTERN_C __declspec(dllexport)
#else
#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))
#endif


#define EE_ENTRY        EXPORT_API void InitImGui()\
                        {\
                            ::Engine::ImGuiHelper::ResetImGuiState();\
                        }\
                        EXPORT_API void LoadExtension(Engine::EExtensionInitializer& data)

