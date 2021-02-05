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

void EUIField::Render() 
{
    if (!fVisible) { return; }
    ImGui::PushID(fId);
    if (OnRender())
    {
        for (ERef<EUIField> field : fChildren)
        {
            field->Render();
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
    if (ImGui::IsItemClicked() && fOnClickCallback) { fOnClickCallback(); }
}

ERef<EUIField> EUIField::AddChild(const ERef<EUIField>& child) 
{
    fChildren.push_back(child);
    return fChildren.back();
}

void EUIField::ClearChildren()
{
    fChildren.clear();
}

void EUIField::SetOnClick(EUICallbackFn fn) 
{
    fOnClickCallback = fn;
}

void EUIField::SetVisible(bool visible) 
{
    fVisible = visible;
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


// ----------------------------------
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

// ----------------------------------
// Component Container
EComponentContainer::EComponentContainer(const EString& componentName) 
    : fComponentName(componentName)
{
    
}

const EString& EComponentContainer::GetDisplayName() const 
{
    return fComponentName;
}

bool EComponentContainer::OnRender() 
{
    return ImGui::CollapsingHeader(fComponentName.c_str());
}

void EComponentContainer::OnRenderEnd() 
{
    EUIField::OnRenderEnd();
}


// ----------------------------------------
// Main Menu Bar
EMainMenuBar::EMainMenuBar() 
{

}

const EString& EMainMenuBar::GetDisplayName() const 
{
    static const EString mainMenuDisplayName = "MainMenu";
    return mainMenuDisplayName;
}

bool EMainMenuBar::OnRender() 
{
    return fOpen = ImGui::BeginMainMenuBar();
}

void EMainMenuBar::OnRenderEnd() 
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
