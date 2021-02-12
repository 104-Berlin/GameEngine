#include "Engine.h"

using namespace Engine;

EObject::EObject(EEntity handle, EScene* scene)
{
    Set(handle, scene);
}

void EObject::Set(EEntity entity, EScene* scene) 
{
    fScene = scene;
    fHandle = entity;
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
    OnSetJsObject(ref);
}

void EObject::OnFromJsObject(const EJson& ref)
{
    
}

void EObject::OnSetJsObject(EJson& ref) const
{
    
}