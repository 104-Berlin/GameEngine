#include "Engine.h"

using namespace Engine;

void EUIManager::RegisterPanel(ERef<EUIPanel> panel) 
{
    fRegisteredPanels.push_back(panel);   
}
