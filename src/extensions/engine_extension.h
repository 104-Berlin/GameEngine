#include "std_include.h"

namespace Engine {
    class EObject;
}

#include "../scene/engine_uuid.h"

#include "../properties/engine_json_converter.h"
#include "../properties/engine_property.h"
#include "../scene/engine_scene.h"
#include "../scene/object/engine_object.h"

#define EUI_NO_IMPL
#include "../ui/engine_ui_functions.h"
#include "../ui/engine_ui_fields.h"
#include "../ui/engine_panels.h"
#include "../ui/engine_ui_manager.h"
#include "engine_extension_manager.h"

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))


#define EE_ENTRY        EXPORT_API void InitImGui(ImGuiContext* context)\
                        {\
                            ImGui::SetCurrentContext(context);\
                        }\
                        EXPORT_API void LoadExtension(Engine::EExtensionInitializer& data)

