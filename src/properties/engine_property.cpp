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

EObjectRef::EObjectRef(const EString& propertyName) 
    : EBaseProperty(propertyName)
{
    fObject = new EObject();
    fObjectUuid = EUUID();
}

EObjectRef::~EObjectRef() 
{
    delete fObject;
}

void EObjectRef::SetValue(const EObject& value) 
{
    if (*fObject == value) { return; }

    for (const auto& f : fBeforeChangeCallbacks) {f.second();}

    std::cout << "Changing ObjectRef \"" << GetPropertyName() << "\"" << " from handle " << (u32)fObject->GetHandle() << " TO " << (u32)value.GetHandle() << std::endl;
    fObject->Set(value);
    fObjectUuid = fObject->GetUuid();

    for (const auto& f : fAfterChangeCallbacks) {f.second();}
}

EObject& EObjectRef::GetValue() const
{
    if (!fObject && fObjectUuid.IsValid())
    {
        fObject->Set(EApplication::gApp().GetActiveScene()->GetObjectByUuid(fObjectUuid));
    }
    return *fObject;
}

void EObjectRef::OnFromJsObject(const EJson& ref) 
{
    // TODO: impl
}

void EObjectRef::OnSetJsObject(EJson& ref) const
{
    // TODO: impl
}

ERef<EResource> _intern::GetResourceFromActiveScene(const EString& enginePath) 
{
    return EApplication::gApp().GetActiveScene()->GetResourceManager().GetResource<EResource>(enginePath);    
}