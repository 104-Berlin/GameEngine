#include "Engine.h"

using namespace Engine;

EBaseProperty::EBaseProperty(EObject* object, const EString& name)
    : fName(name), fObject(object)
{
    object->AddProperty(this);
}

void EBaseProperty::FromJsObject(const EJson& ref)
{
    OnFromJsObject(ref);
}

void EBaseProperty::SetJsObject(EJson& ref) const
{
    OnSetJsObject(ref);
}

void EBaseProperty::OnFromJsObject(const EJson& ref)
{

}

void EBaseProperty::OnSetJsObject(EJson& ref) const
{
    
}

const EString& EBaseProperty::GetPropertyName() const
{
    return fName;
}

void EBaseProperty::SetPropertyName(const EString& name)
{
    fName = name;
}

void EBaseProperty::AddEventBeforeChange(const EChangeFunc& func)
{
    fBeforeChangeCallbacks.push_back(func);
}

void EBaseProperty::AddEventAfterChange(const EChangeFunc& func)
{
    fAfterChangeCallbacks.push_back(func);
}