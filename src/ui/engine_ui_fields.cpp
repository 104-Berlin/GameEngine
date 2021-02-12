#include "Engine.h"
#include <imgui_internal.h>

using namespace Engine;


// ----------------------------------
// Basic UI Field

EUIField::EUIField() 
{
    fVisible = true;
    fId = next_ui_id();
}

void EUIField::UpdateEvents() 
{
    fEventDispatcher.Update();
    for (ERef<EUIField> child : fChildren)
    {
        child->UpdateEvents();
    }
}

void EUIField::Render() 
{
    if (!fVisible) { return; }
    if (fIsDirty && fCustomUpdateFunction)
    {
        fCustomUpdateFunction(shared_from_this());
    }
    fIsDirty = false;
    ImGui::PushID(fId);
    if (OnRender())
    {
        for (ERef<EUIField> field : fChildren)
        {
            field->Render();
        }
    }
    if (!fDragData.Type.empty())
    {
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload(fDragData.Type.c_str(), fDragData.Buffer, fDragData.Size);
            ImGui::EndDragDropSource();
        }
    }
    if (fDropFunction.second)
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(fDropFunction.first.c_str()))
            {
                EDragData data;
                data.Type = fDropFunction.first;
                data.Buffer = payload->Data;
                data.Size = payload->DataSize;
                fDropFunction.second(data);
            }
            ImGui::EndDragDropTarget();
        }
    }
    OnRenderEnd();

    if (GImGui->CurrentWindow->IDStack.Size > 1)
    {
        ImGui::PopID();
    }
}

bool EUIField::OnRender() 
{
    return true;
}

void EUIField::OnRenderEnd() 
{
    if (ImGui::IsItemClicked()) 
    { 
        fEventDispatcher.Enqueue<EUIClickEvent>(EUIClickEvent());
    }
}

void EUIField::SetUpdateFunction(UpdateFunction function) 
{
    fCustomUpdateFunction = function;   
}

ERef<EUIField> EUIField::AddChild(const ERef<EUIField>& child) 
{
    if (!child) { return nullptr; }
    fChildren.push_back(child);
    return fChildren.back();
}

void EUIField::ClearChildren()
{
    fChildren.clear();
}

void EUIField::SetVisible(bool visible) 
{
    fVisible = visible;
}

void EUIField::SetDirty(bool value) 
{
    fIsDirty = value;
    for (ERef<EUIField> child : fChildren)
    {
        child->SetDirty(value);
    }
}

bool EUIField::IsDirty() const
{
    if (fIsDirty) { return true; }
    for (ERef<EUIField> child : fChildren)
    {
        if (child->IsDirty()) { return true; }
    }
    return false;
}

void EUIField::SetDragData(EDragData data) 
{
    fDragData = {};
    fDragData.Type = data.Type;
    fDragData.Size = data.Size;
    fDragData.Buffer = malloc(data.Size);
    memcpy(fDragData.Buffer, data.Buffer, data.Size);    
}

void EUIField::OnDrop(const EString& type, DropFunction dropFunction) 
{
    fDropFunction = {type, dropFunction};
}

EEventDispatcher& EUIField::GetEventDispatcher() 
{
    return fEventDispatcher;
}

// --------------------------------
// UI Label

EUILabel::EUILabel(const EString& label) 
    : fLabel(label)
{

}

const EString& EUILabel::GetDisplayName() const 
{
    return fLabel;
}

bool EUILabel::OnRender() 
{
    ImGui::Text("%s", fLabel.c_str());
    return true;
}

// --------------------------------
// UI Container just to manage children
EUIContainer::EUIContainer(const EString& identifier) 
    : fStringId(identifier)
{
    
}

const EString& EUIContainer::GetDisplayName() const 
{
    return fStringId;
}

bool EUIContainer::OnRender() 
{
    return true;
}


// ----------------------------------------------------------------------------------------------------
// UI Panel

EUIPanel::EUIPanel(const EString& panelName) 
    : fName(panelName), fOpen(true), fWasJustClosed(false)
{
    
}

const EString& EUIPanel::GetDisplayName() const 
{
    return fName;
}

bool EUIPanel::OnRender() 
{
    EUIField::OnRender();
    if (fOpen)
    {
        ImGui::Begin(GetDisplayName().c_str(), &fOpen);
        if (!fOpen) { fWasJustClosed = true; }
    }
    return fOpen;
}

void EUIPanel::OnRenderEnd() 
{
    EUIField::OnRenderEnd();
    if (fOpen || fWasJustClosed)
    {
        fWasJustClosed = false;
        ImGui::End();
    }
}

void EUIPanel::Open() 
{
    fOpen = true;
}

bool EUIPanel::IsOpen() const
{
    return fOpen;
}



// ----------------------------------------------------------------------------------------------------
// UI Input Field String
EUIInputFieldString::EUIInputFieldString(const EString& label) 
    : fLabel(label)
{
    memset(fValue, 0, STRING_BUFFER_SIZE);
}

const EString& EUIInputFieldString::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldString::OnRender() 
{
    if (ImGui::InputText(fLabel.c_str(), fValue, STRING_BUFFER_SIZE, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EStringChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldString::SetValue(const EString& value) 
{
    if (value.length() > STRING_BUFFER_SIZE) { std::cout << "String is to big to be displayed in input field string" << std::endl; return; }
    strcpy(fValue, value.c_str());
}

EString EUIInputFieldString::GetValue() const
{
    return EString(fValue);
}

// --------------------------------------------------------------------
// Integer Input Field
EUIInputFieldInteger::EUIInputFieldInteger(const EString& label) 
    : fLabel(label), fValue(0)
{
    
}

const EString& EUIInputFieldInteger::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldInteger::OnRender() 
{
    if (ImGui::InputInt(fLabel.c_str(), &fValue, 1, 100, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EIntegerChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldInteger::SetValue(i32 value) 
{
    fValue = value;
}

i32 EUIInputFieldInteger::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Float Input Field
EUIInputFieldFloat::EUIInputFieldFloat(const EString& label) 
    : fLabel(label), fValue(0)
{
    
}

const EString& EUIInputFieldFloat::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldFloat::OnRender() 
{
    if (ImGui::InputFloat(fLabel.c_str(), &fValue, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EFloatChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat::SetValue(float value) 
{
    fValue = value;
}

float EUIInputFieldFloat::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Float Input2 Field
EUIInputFieldFloat2::EUIInputFieldFloat2(const EString& label) 
    : fLabel(label), fValue(0.0f)
{
    
}

const EString& EUIInputFieldFloat2::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldFloat2::OnRender() 
{
    if (ImGui::InputFloat2(fLabel.c_str(), &fValue.x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EFloat2ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat2::SetValue(const EVec2& value) 
{
    fValue = value;
}

EVec2 EUIInputFieldFloat2::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Input Field Float3
EUIInputFieldFloat3::EUIInputFieldFloat3(const EString& label) 
    : fLabel(label), fValue(0.0f)
{
    
}

const EString& EUIInputFieldFloat3::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldFloat3::OnRender() 
{
    if (ImGui::InputFloat3(fLabel.c_str(), &fValue.x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EFloat3ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat3::SetValue(const EVec3& value) 
{
    fValue = value;
}

EVec3 EUIInputFieldFloat3::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Input Field Float4
EUIInputFieldFloat4::EUIInputFieldFloat4(const EString& label) 
    : fLabel(label), fValue(0.0f)
{
    
}

const EString& EUIInputFieldFloat4::GetDisplayName() const 
{
    return fLabel;
}

bool EUIInputFieldFloat4::OnRender() 
{
    if (ImGui::InputFloat4(fLabel.c_str(), &fValue.x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
    {
        fEventDispatcher.Enqueue<EFloat4ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat4::SetValue(const EVec4& value) 
{
    fValue = value;
}

EVec4 EUIInputFieldFloat4::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Checkbox
EUICheckbox::EUICheckbox(const EString& label) 
    : fLabel(label), fValue(false)
{
    
}

const EString& EUICheckbox::GetDisplayName() const 
{
    return fLabel;
}

bool EUICheckbox::OnRender() 
{
    if (ImGui::Checkbox(fLabel.c_str(), &fValue))
    {
        fEventDispatcher.Enqueue<ECheckboxChangeEvent>({GetValue()});
    }
    return true;
}

void EUICheckbox::SetValue(bool value) 
{
    fValue = value;
}

bool EUICheckbox::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Component Container
EUIComponentContainer::EUIComponentContainer(const EString& componentName) 
    : fComponentName(componentName)
{
    
}

const EString& EUIComponentContainer::GetDisplayName() const 
{
    return fComponentName;
}

bool EUIComponentContainer::OnRender() 
{
    return ImGui::CollapsingHeader(fComponentName.c_str());
}

void EUIComponentContainer::OnRenderEnd() 
{
    EUIField::OnRenderEnd();
}


// ----------------------------------------
// Main Menu Bar
EUIMainMenuBar::EUIMainMenuBar() 
{

}


const EString& EUIMainMenuBar::GetDisplayName() const 
{
    static const EString mainMenuDisplayName = "MainMenu";
    return mainMenuDisplayName;
}

bool EUIMainMenuBar::OnRender() 
{
    return fOpen = ImGui::BeginMainMenuBar();
}

void EUIMainMenuBar::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndMainMenuBar();
    }
}


// ----------------------------------------
// Menu
EUIMenu::EUIMenu(const EString& displayName) 
    : fDisplayName(displayName), fOpen(false)
{
    
}

const EString& EUIMenu::GetDisplayName() const 
{
    return fDisplayName;
}

bool EUIMenu::OnRender() 
{
    return fOpen = ImGui::BeginMenu(fDisplayName.c_str());
}

void EUIMenu::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndMenu();
    }
    
}


// ----------------------------------------
// Context Menu
EUIContextMenu::EUIContextMenu(const EString& displayName) 
    : fDisplayName(displayName), fOpen(false)
{
    
}

const EString& EUIContextMenu::GetDisplayName() const 
{
    return fDisplayName;
}

bool EUIContextMenu::OnRender() 
{
    return fOpen = ImGui::BeginPopupContextWindow();
}

void EUIContextMenu::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndPopup();
    }
}

// ----------------------------------------
// Menu Item
EUIMenuItem::EUIMenuItem(const EString& label) 
    : fLabel(label)
{
    
}

const EString& EUIMenuItem::GetDisplayName() const 
{
    return fLabel;
}

bool EUIMenuItem::OnRender() 
{
    ImGui::MenuItem(fLabel.c_str());
    return true;
}

// ----------------------------------------
// Selectable
EUISelectable::EUISelectable(const EString& label) 
    : fLabel(label)
{
    
}

const EString& EUISelectable::GetDisplayName() const 
{
    return fLabel;
}

bool EUISelectable::OnRender() 
{
    ImGui::Selectable(fLabel.c_str());
    return true;
}
