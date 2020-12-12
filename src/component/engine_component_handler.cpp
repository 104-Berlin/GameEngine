#include "Engine.h"

using namespace Engine;

EComponentHandler::EComponentHandler(size_t initialSize)
    : fInitialSize(initialSize)
{

}

EComponentHandler::~EComponentHandler()
{
    for (auto& entry : fComponentStorage)
    {
        for (EComponent* component : entry.second)
        {
            delete component;
        }
    }
    fComponentStorage.clear();
    fComponent_Object_Storage.clear();
}

void* EComponentHandler::CreateComponentIntern(const std::type_info& type, size_t singleMemorySize, EObject* object)
{
    EMap<size_t, EVector<EComponent*>>::iterator it = fComponentStorage.find(type.hash_code());

    void* newMemory = malloc(singleMemorySize);

    if (it != fComponentStorage.end())
    {
        it->second.push_back((EComponent*)newMemory);
    }
    else
    {
        fComponent_Object_Storage[object] = {(EComponent*)newMemory};
        fComponentStorage[type.hash_code()] = {(EComponent*)newMemory};
    }


    return newMemory;
}

void EComponentHandler::Render()
{
    for (auto& entry : fComponent_Object_Storage)
    {
        for (EComponent* comp : entry.second)
        {
            comp->Render();
        }
    }
}

void EComponentHandler::Update(float delta)
{
    for (auto& entry : fComponent_Object_Storage)
    {
        for (EComponent* comp : entry.second)
        {
            comp->Update(delta);
        }
    }
}

void EComponentHandler::RenderUI()
{
    for (auto& entry : fComponent_Object_Storage)
    {
        for (EComponent* comp : entry.second)
        {
            comp->RenderUI();
        }
    }
}


EVector<EComponent*> EComponentHandler::GetComponentStorage(const std::type_info& type)
{
    EMap<size_t, EVector<EComponent*>>::iterator it = fComponentStorage.find(type.hash_code());
    if (it !=  fComponentStorage.end())
    {
        return it->second;
    }
    return {};
}

EVector<EComponent*> EComponentHandler::GetComponentStorage(EObject* object)
{
    EMap<EObject*, EVector<EComponent*>>::iterator it = fComponent_Object_Storage.find(object);
    if (it !=  fComponent_Object_Storage.end())
    {
        return it->second;
    }
    return {};
}
