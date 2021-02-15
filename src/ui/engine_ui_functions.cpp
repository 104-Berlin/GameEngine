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

ERef<EUIField> UI::CreateInputField_Bool(const EString& label, EProperty<bool>* property) 
{
    ERef<EUICheckbox> result = EMakeRef(EUICheckbox, label);
    result->OnValueChange([property](ECheckboxChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_Float(const EString& label, EProperty<float>* property) 
{
    ERef<EUIInputFieldFloat> result = EMakeRef(EUIInputFieldFloat, label);
    result->OnValueChange([property](EFloatChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_Double(const EString& label, EProperty<double>* property) 
{
    ERef<EUIInputFieldFloat> result = EMakeRef(EUIInputFieldFloat, label);
    result->OnValueChange([property](EFloatChangeEvent event){
        property->SetValue((double)event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_I32(const EString& label, EProperty<i32>* property) 
{
    ERef<EUIInputFieldInteger> result = EMakeRef(EUIInputFieldInteger, label);
    result->OnValueChange([property](EIntegerChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_Vec3(const EString& label, EProperty<EVec3>* property) 
{
    ERef<EUIInputFieldFloat3> result = EMakeRef(EUIInputFieldFloat3, label);
    result->OnValueChange([property](EFloat3ChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_Vec4(const EString& label, EProperty<EVec4>* property)
{
    ERef<EUIInputFieldFloat4> result = EMakeRef(EUIInputFieldFloat4, label);
    result->OnValueChange([property](EFloat4ChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_String(const EString& label, EProperty<EString>* property)
{
    ERef<EUIInputFieldString> result = EMakeRef(EUIInputFieldString, label);
    result->OnValueChange([property](EStringChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetValue(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_UUID(const EString& label, EProperty<EUUID>* property)
{
    ERef<EUILabel> result = EMakeRef(EUILabel, property->GetValue().ToString());
    return result; 
}

ERef<EUIField> UI::CreateInputField_Mesh(const EString& label, EObjectProperty<EMesh>* property) 
{
    ERef<EUIMeshInput> result = EMakeRef(EUIMeshInput);
    result->OnValueChange([property](EMeshChangeEvent event){
        property->SetValue(event.Value);
    });
    return result;
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