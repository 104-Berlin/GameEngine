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

void UI::RenderInputField_Bool(const EString& label, EProperty<bool>* value)
{
    bool val = value->GetValue();
    if (ImGui::Checkbox(label.c_str(), &val))
    {
        value->SetValue(val);
    }
}

void UI::RenderInputField_Float(const EString& label, EProperty<float>* value)
{
    double val = value->GetValue();
    if (ImGui::InputDouble(label.c_str(), &val, 0.0f, 0.0f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
    {   
        value->SetValue(val);
    }
}

void UI::RenderInputField_Double(const EString& label, EProperty<double>* value)
{
    float val = value->GetValue();
    if (ImGui::DragFloat(label.c_str(), &val))
    {
        value->SetValue(val);
    }
}

void UI::RenderInputField_I32(const EString& label, EProperty<i32>* value)
{
    i32 val = value->GetValue();
    if (ImGui::DragInt(label.c_str(), &val))
    {
        value->SetValue(val);
    }
}

void UI::RenderInputField_Vec3(const EString& label, EProperty<EVec3>* value)
{
    EVec3 val = value->GetValue();
    if (ImGui::DragFloat3(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
    {
        value->SetValue(val);
    }

}


void UI::RenderInputField_Vec4(const EString& label, EProperty<EVec4>* value)
{
    EVec4 val = value->GetValue();
    if (ImGui::DragFloat4(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
    {
        value->SetValue(val);
    }
}

void UI::RenderInputField_String(const EString& label, EProperty<EString>* value)
{
    size_t bufferSize = 255;
    char* buffer = new char[bufferSize];
    memset(buffer, 0, bufferSize);
    strcpy(buffer, value->GetValue().c_str());
    if (ImGui::InputText(label.c_str(), buffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        value->SetValue(buffer);
        std::cout << "String changed" << std::endl;
    }
    delete[] buffer;
}

void UI::RenderInputField_UUID(const EString& label, EProperty<EUUID>* value)
{
    ImGui::Text("%s", label.c_str());
    ImGui::SameLine();
    ImGui::Text("%s", value->GetValue().ToString().c_str());
}