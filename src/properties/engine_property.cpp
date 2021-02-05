#include "Engine.h"

using namespace Engine;

EBaseProperty::EBaseProperty(const EString& name)
    : fName(name)
{
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

void EBaseProperty::AddEventBeforeChange(intptr_t key, const EChangeFunc& func)
{
    fBeforeChangeCallbacks[key] = func;
}

void EBaseProperty::AddEventAfterChange(intptr_t key, const EChangeFunc& func)
{
    fAfterChangeCallbacks[key] = func;
}
