#include "Engine.h"

using namespace Engine;

EObject::EObject(EEntity handle, EScene* scene)
{
    fScene = scene;
    fHandle = handle;
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