#include "../Engine.h"

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

