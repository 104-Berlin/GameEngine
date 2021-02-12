#include "Engine.h"

using namespace Engine;



EScene::EScene(const EString& name)
    : fName(name), 
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
