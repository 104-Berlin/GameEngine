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

bool UI::IsItemJustReleased() 
{
    return IsItemActiveLastFrame() && !ImGui::IsItemActive();
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
    result->SetMesh(property->GetValue());
    return result;
}

ERef<EUIField> UI::CreateInputField_Texture(const EString& label, EObjectProperty<ETexture2D>* property) 
{
    ERef<EUITextureInput> result = EMakeRef(EUITextureInput);
    result->OnValueChange([property](ETextureChangeEvent event){
        property->SetValue(event.Value);
    });
    result->SetTexture(property->GetValue());
    return result;
}