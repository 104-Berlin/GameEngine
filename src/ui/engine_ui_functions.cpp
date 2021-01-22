#include "Engine.h"

#include <imgui_internal.h>

using namespace Engine;


bool UI::IsItemActiveLastFrame() 
{
    ImGuiContext& g = *GImGui;
    if (g.ActiveIdPreviousFrame)
        return g.ActiveIdPreviousFrame == g.CurrentWindow->DC.LastItemId;
    return false;
}