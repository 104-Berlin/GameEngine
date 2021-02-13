#include "Engine.h"

using namespace Engine;

EObject::EObject(EEntity handle, EScene* scene)
{
    Set(handle, scene);
}

void EObject::Set(EEntity entity, EScene* scene) 
{
    fHandle = entity;
    fScene = scene;
}

void EObject::Set(EObject object) 
{
    Set(object.fHandle, object.fScene);
}

void EObject::FromJsObject(const EJson& ref)
{
    OnFromJsObject(ref);
}

void EObject::SetJsObject(EJson& ref) const
{
    for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
    {
        if (compDsc->Has(*this))
        {
            compDsc->SetJsObject(*this, ref[compDsc->Name]);
        }   
    }
    OnSetJsObject(ref);
}

void EObject::OnFromJsObject(const EJson& ref)
{
    
}

void EObject::OnSetJsObject(EJson& ref) const
{
    
}


