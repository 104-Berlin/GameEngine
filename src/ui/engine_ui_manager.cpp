#include "Engine.h"

using namespace Engine;

void ImGuiHelper::ResetImGuiState() 
{
    EApplication::gApp().ResetImGuiContext();   
}


EVector<ERef<EUIPanel>> EUIManager::GetPanels() const
{
    return fRegisteredPanels;    
}

void EUIManager::RegisterPanel(ERef<EUIPanel> panel) 
{
    fRegisteredPanels.push_back(panel);   
}
