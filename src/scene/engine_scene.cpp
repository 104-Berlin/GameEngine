#include "Engine.h"

using namespace Engine;


EScene::EScene(const EString& name)
    : fName("Name", name), 
    fSelectedObject("SelectedObject")
{
}

EScene::~EScene()
{
    std::cout << "Scene \"" << fName.GetValue() << "\" Deleted!" << std::endl;
}

EResourceManager& EScene::GetResourceManager() 
{
    return fResourceManager;
}

void EScene::Update(float delta)
{
}

EObjectRef& EScene::GetSelectedObject() 
{
    return fSelectedObject;
}

EObject EScene::GetObjectByUuid(const EUUID& uuid)
{
    return fEntityMap[uuid];
}

void EScene::SetJsObject(EJson& json)
{
    fName.SetJsObject(json);
    EJson& objectArray = json["Objects"] = EJson::array();
    ForEachObject([&objectArray](EObject object) mutable {
        EJson objectJson = EJson::object();
        object.SetJsObject(objectJson);
        objectArray.push_back(objectJson);
    });
}

void EScene::FromJsObject(const EJson& json) 
{
    fName.FromJsObject(json);

    const EJson& objectArray = json["Objects"];
    if (objectArray.is_array())
    {
        fRegistry.clear();
        for (const EJson& objectJson : objectArray)
        {
            EObject newObject = CreateObject();
            newObject.FromJsObject(objectJson);
        }
    } 
}

void EScene::Clear() 
{
    fRegistry.clear();
}

void EScene::ForEachObject(ObjectCallback fn)
{
    fRegistry.each([this, fn](EEntity entity){
        this->CallObjectFunc(entity, fn);
    }); 
}

void EScene::CallObjectFunc(EEntity entity, ObjectCallback fn) 
{
    fn(EObject(entity, this));
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);

    // Make sure we dont have the uuid registered allready
    EUUID newUuid = EUUID().CreateNew();
    while (fEntityMap.find(newUuid) != fEntityMap.end())
    {
        newUuid = EUUID().CreateNew();
    }
    // -----------------------------------


    object.AddComponent<ETagComponent>("Empty Object", newUuid);
    object.AddComponent<ETransformComponent>();
    fEntityMap.insert({ newUuid, object });
    return object;
}
