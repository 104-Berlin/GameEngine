#include <extensions/engine_extension.h>


struct SomeComponent
{
    REFLACTABLE(
        (Engine::EProperty<float>, SomeValue)
    )
};


EE_ENTRY
{
    data.componentData.RegisterComponent<SomeComponent>("Fancy Some Component");
}