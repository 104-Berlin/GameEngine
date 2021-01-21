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
    if (OnRender())
    {
        for (ERef<EUIField> field : fChildren)
        {
            field->Render();
        }
    }
    OnRenderEnd();
}

bool EUIField::OnRender() 
{
    return true;
}

void EUIField::OnRenderEnd() 
{
    
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
// UI Input Field
EInputField::EInputField(EBaseProperty* property) 
    : fProperty(property)
{
    
}

const EString& EInputField::GetDisplayName() const
{
    return fProperty->GetPropertyName();    
}

bool EInputField::OnRender() 
{
    UI::RenderInputField(fProperty->GetPropertyName(), fProperty);
    return true; // ?
}



// ----------------------------------
// UI Input Field
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