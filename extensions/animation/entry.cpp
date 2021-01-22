#include <extensions/engine_extension.h>

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))


struct SomeComponent
{
    REFLACTABLE(
        (Engine::EProperty<float>, SomeValue)
    )


    SomeComponent() = default;
    SomeComponent(const SomeComponent&) = default;
};



EXPORT_API void LoadExtension(Engine::EExtensionInitializer& data)
{
    data.componentData.RegisterComponent<SomeComponent>("FancySomeComponent");
}