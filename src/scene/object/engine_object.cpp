#include "Engine.h"

using namespace Engine;

EObject::EObject()
{
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