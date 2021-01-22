#include "Engine.h"

using namespace Engine;

void EPanelComponentData::AddComponentDescription(ComponentDescription* dsc) 
{
    EPanelComponentData::sComponentDescriptions.push_back(dsc);   
}

const EVector<ComponentDescription*>& EPanelComponentData::GetComponentDescription() 
{
    return sComponentDescriptions;
}

EPanelComponentData& EPanelComponentData::data() 
{
    static EPanelComponentData data;
    return data;
    
}

EComponentPanel::EComponentPanel() 
    : EUIPanel("Components")
{
    
}

void EComponentPanel::SetObjectToDisplay(EObject object) 
{
    fActiveObject = object;
    UpdateComponents();
}

bool EComponentPanel::OnRender() 
{
    EUIPanel::OnRender();
    
    if (!fActiveObject) { return false; }
    if (ImGui::BeginPopupContextWindow())
    {
        for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
        {
            if (ImGui::MenuItem(compDsc->Name.c_str()))
            {
                compDsc->Create(fActiveObject);
                UpdateComponents();
            }
        }
        ImGui::EndPopup();
    }
    return true;
}

void EComponentPanel::UpdateComponents() 
{
    ClearChildren();
    if (!fActiveObject) { return; }
    for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
    {
        if (compDsc->Has(fActiveObject))
        {
            AddChild(compDsc->CreateUIField(fActiveObject));
            //ERef<EUIField> componentContainer = AddChild(EMakeRef(EComponentContainer, compDsc->Name));
        }
    }
}