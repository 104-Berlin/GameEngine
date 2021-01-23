#include "Engine.h"

using namespace Engine;


// ----------------------------------
// Basic UI Field

EUIField::EUIField() 
{
    fId = next_ui_id();
}

void EUIField::Render() 
{
    ImGui::PushID(fId);
    if (OnRender())
    {
        for (ERef<EUIField> field : fChildren)
        {
            field->Render();
        }
    }
    OnRenderEnd();
    ImGui::PopID();
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


// ----------------------------------
// UI Panel

EUIPanel::EUIPanel(const EString& panelName) 
    : fName(panelName)
{
    
}

const EString& EUIPanel::GetDisplayName() const 
{
    return fName;
}

bool EUIPanel::OnRender() 
{
    EUIField::OnRender();
    ImGui::Begin(GetDisplayName().c_str(), &fOpen);
    return fOpen;
}

void EUIPanel::OnRenderEnd() 
{
    EUIField::OnRenderEnd();
    ImGui::End();
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
EMenu::EMenu(const EString& displayName) 
    : fDisplayName(displayName), fOpen(false)
{
    
}

const EString& EMenu::GetDisplayName() const 
{
    return fDisplayName;
}

bool EMenu::OnRender() 
{
    return fOpen = ImGui::BeginMenu(fDisplayName.c_str());
}

void EMenu::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndMenu();
    }
    
}

// ----------------------------------------
// Menu Item
EMenuItem::EMenuItem(const EString& label) 
    : fLabel(label)
{
    
}

const EString& EMenuItem::GetDisplayName() const 
{
    return fLabel;
}

bool EMenuItem::OnRender() 
{
    ImGui::MenuItem(fLabel.c_str());
    return true;
}
