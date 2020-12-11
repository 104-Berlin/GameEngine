#include "Engine.h"

using namespace Engine;

EObject::EObject(const EString& name, const EUUID& uuid)
    :   fAllProperties(),
        fUuid(uuid),
        fName(this, "Name")
{
    fName.SetValue(name);
}

void EObject::FromJsObject(const EJson& ref)
{
    OnFromJsObject(ref);
}

void EObject::SetJsObject(EJson& ref) const
{
    ref["UUID"] = JSHelper::ConvertValue(fUuid);
    OnSetJsObject(ref);
}

void EObject::OnFromJsObject(const EJson& ref)
{

}

void EObject::OnSetJsObject(EJson& ref) const
{
    ref["UUID"] = JSHelper::ConvertValue(fUuid);
}

void EObject::AddProperty(EBaseProperty* prop)
{
    EString propName = prop->GetPropertyName();
    fAllProperties[propName] = prop;
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

void EObject::SetName(const EString& name)
{
    fName.SetValue(name);
}

const EString& EObject::GetName() const
{
    return fName.GetValue();
}

const EUUID& EObject::GetUuid() const
{
    return fUuid;
}

void EObject::Render()
{
    OnRender();
}

void EObject::OnRender()
{
}

void EObject::Update(float delta)
{
    OnUpdate(delta);
}

void EObject::OnUpdate(float delta)
{
}

void EObject::RenderUI()
{
    OnRenderUI();
}

void EObject::OnRenderUI()
{

}
