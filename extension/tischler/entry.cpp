#include "extensions/engine_extension.h"


struct ExtensionComponent
{
    REFLACTABLE(
        (Engine::EProperty<float>, MyFloat)
    )
};

void RegisterPanels(Engine::EUIManager& uiManager)
{
    using namespace Engine;
    ERef<EUIPanel> panel = EMakeRef(EUIPanel, "Extension Panel");
    
    uiManager.RegisterPanel(panel);
}

EE_ENTRY {
    data.componentData.RegisterComponent<ExtensionComponent>("Extension");
    RegisterPanels(data.uiManager);
}
