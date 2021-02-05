#include "Engine.h"

using namespace Engine;


EPanelComponentData::~EPanelComponentData() 
{
    //ClearComponentData();    
}

void EPanelComponentData::AddComponentDescription(ComponentDescription* dsc) 
{
    EPanelComponentData::sComponentDescriptions.push_back(dsc);   
}

const EVector<ComponentDescription*>& EPanelComponentData::GetComponentDescription() 
{
    return sComponentDescriptions;
}

void EPanelComponentData::ClearComponentData() 
{
    for (ComponentDescription* data : sComponentDescriptions)
    {
        delete data;
    }
    sComponentDescriptions.clear();
}

EPanelComponentData& EPanelComponentData::data() 
{
    static EPanelComponentData data;
    return data;
}