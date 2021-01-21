#include "Engine.h"

using namespace Engine;

EVector<ComponentDescription*> EPanelComponentData::sComponentDescriptions;

void EPanelComponentData::AddComponentDescription(ComponentDescription* dsc) 
{
    EPanelComponentData::sComponentDescriptions.push_back(dsc);   
}

const EVector<ComponentDescription*>& EPanelComponentData::GetComponentDescription() 
{
    return sComponentDescriptions;
}


EComponentPanel::EComponentPanel() 
    : EUIPanel("Components")
{
    
}

void EComponentPanel::SetObjectToDisplay(EObject object) 
{
    ClearChildren();
    if (!object) { return; }
    for (ComponentDescription* compDsc : EPanelComponentData::GetComponentDescription())
    {
        if (compDsc->Has(object))
        {
            ERef<EUIField> componentContainer = AddChild(EMakeRef(EComponentContainer, compDsc->Name));
            compDsc->Reflect(object, [componentContainer](const char* name, EBaseProperty* property){
                componentContainer->AddChild(EMakeRef(EInputField, property));
            });
        }
    }
}