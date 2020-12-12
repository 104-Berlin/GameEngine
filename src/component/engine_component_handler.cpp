#include "Engine.h"

using namespace Engine;

EComponentHandler::EComponentStorageEntry::EComponentStorageEntry()
{
    Buffer      = nullptr;
    ByteOffset  = 0;
    CurrentSize = 0;
}

EComponentHandler::EComponentStorageEntry::~EComponentStorageEntry()
{
    if (Buffer)
    {
        delete Buffer;
        Buffer = nullptr;
    }
}


EComponentHandler::EComponentHandler(size_t initialSize)
    : fInitialSize(initialSize)
{

}

EComponentHandler::~EComponentHandler()
{
    for (auto& entry : fComponentStorage)
    {
        if (entry.second)
        {
            delete entry.second;
        }
    }
    fComponentStorage.clear();
    fComponent_Object_Storage.clear();
}

void* EComponentHandler::CreateComponentIntern(const std::type_info& type, size_t singleMemorySize, EObject* object)
{
    void* resultPtr = nullptr;
    EMap<size_t, EComponentStorageEntry*>::iterator it = fComponentStorage.find(type.hash_code());
    if (it != fComponentStorage.end())
    {
        // We have a registry for this componen type
        EComponentStorageEntry* storage = it->second;
        if (!(storage->ByteOffset + singleMemorySize < storage->CurrentSize))
        {
            // Need to resize for adding Component

            size_t newSize  = storage->CurrentSize + (50 * singleMemorySize);

            void* newBuffer = malloc(newSize);
            memset(newBuffer, 0, newSize);
            memcpy(newBuffer, storage->Buffer, storage->CurrentSize);


            delete storage->Buffer;
            storage->Buffer = (u8*) newBuffer;

            storage->CurrentSize = newSize;
        }


        resultPtr = &(storage->Buffer[storage->ByteOffset]);

        // Pointing to empty memory again
        storage->ByteOffset += singleMemorySize;
    }
    else
    {
        // No Components of type exist. Create new registry with fInitialSize element

        size_t bufferSize = fInitialSize * singleMemorySize;

        EComponentStorageEntry* entry = new EComponentStorageEntry();
        entry->Buffer = (u8*)malloc(bufferSize);
        memset(entry->Buffer, 0, bufferSize);

        entry->ByteOffset = singleMemorySize;
        entry->CurrentSize = bufferSize;

        fComponentStorage[type.hash_code()] = entry;
        
        resultPtr = entry->Buffer;
    }

    if (fComponent_Object_Storage.find(object) != fComponent_Object_Storage.end())
    {
        fComponent_Object_Storage[object].push_back((EComponent*)resultPtr);
    }
    else
    {
        fComponent_Object_Storage[object] = {(EComponent*)resultPtr};
    }

    return resultPtr;
}

EComponentHandler::EComponentStorageEntry* EComponentHandler::GetComponentStorage(const std::type_info& type)
{
    EMap<size_t, EComponentStorageEntry*>::iterator it = fComponentStorage.find(type.hash_code());
    if (it !=  fComponentStorage.end())
    {
        return it->second;
    }
    return nullptr;
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