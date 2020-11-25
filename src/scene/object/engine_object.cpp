#include "Engine.h"

using namespace Engine;

EObject::EObject(const EString& name, const EUUID& uuid)
    :   fUuid(uuid),
        fName(this, "Name")
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

void EObject::AddProperty(EBaseProperty* prop)
{
    fAllProperties[prop->GetPropertyName()] = prop;
}

EBaseProperty* EObject::GetPropertyByName(const EString& name)
{
    return fAllProperties[name];
}

const EBaseProperty* EObject::GetPropertyByName(const EString& name) const
{
    EMap<EString, EBaseProperty*>::const_iterator it = fAllProperties.find(name);
    if (it != fAllProperties.end())
    {
        return it->second;
    }
    return nullptr;
}