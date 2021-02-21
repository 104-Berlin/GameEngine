#define GLFW_DLL
#include <extensions/engine_extension.h>

struct ExtensionComponent
{
    REFLACTABLE(
        (Engine::EProperty<float>, MyFloat)
    )
};

EE_ENTRY {
    data.componentData.RegisterComponent<ExtensionComponent>("Extension");
    //std::cout << "Loading extension!" << std::endl;
}
