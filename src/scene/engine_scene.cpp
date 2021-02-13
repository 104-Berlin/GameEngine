#include "Engine.h"

using namespace Engine;



EObjectReference::EObjectReference(const EString& refName) 
    : EBaseProperty(refName)
{
    fObject = new EObject(entt::null, nullptr);
}

EObjectReference::~EObjectReference() 
{
    delete fObject;
}

void EObjectReference::SetValue(EObject object) 
{
    if (*fObject == object) { return; }

    for (const auto& cb : fBeforeChangeCallbacks) { cb.second(); }

    fObject->Set(object);

    for (const auto& cb : fAfterChangeCallbacks) { cb.second(); }
}

EObject EObjectReference::GetValue() 
{
    return *fObject;
}

void EObjectReference::OnFromJsObject(const EJson& ref) 
{
    if (fObject && JSHelper::HasParam(ref, GetPropertyName()))
    {
        fObject->FromJsObject(ref[GetPropertyName()]);
    }
}

void EObjectReference::OnSetJsObject(EJson& ref) const
{
    if (JSHelper::HasParam(ref, GetPropertyName()))
    {
        if (ref[GetPropertyName()].size() > 0)
        {
            // Get by uuid or something
        }
        else
        {
            fObject->Set(entt::null, nullptr);
        }
    }
}






EScene::EScene(const EString& name)
    : fName("Name", name), 
    fSelectedObject("SelectedObject")
{
}

EScene::~EScene()
{
}

void EScene::Update(float delta)
{
}

EObjectRef& EScene::GetSelectedObject() 
{
    return fSelectedObject;
}

void EScene::SetJsObject(EJson& json)
{
    fName.SetJsObject(json);
    EJson& objectArray = json["Objects"] = EJson::array();
    ForEachObject([&objectArray](EObject object){
        object.SetJsObject(objectArray.back());
    });
}

void EScene::FromJsObject(const EJson& json) 
{
    fName.FromJsObject(json);
    u32 counter = 0;
    ForEachObject([&json, &counter](EObject object) mutable {
        object.FromJsObject(json["Objects"][counter++]);
    });
}

void EScene::ForEachObject(ObjectCallback fn)
{
    fRegistry.each([this, fn](EEntity entity){
        fn(EObject(entity, this));
    }); 
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    object.AddComponent<ETransformComponent>();
    object.AddComponent<ENameComponent>("Empty Object");
    return object;
}
