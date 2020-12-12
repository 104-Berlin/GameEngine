#pragma once

namespace Engine {


    class EComponentHandler
    {
    private:
        struct EComponentStorageEntry
        {
            EComponentStorageEntry();
            EComponentStorageEntry(const EComponentStorageEntry& other) = delete;
            ~EComponentStorageEntry();
            void operator=(const EComponentStorageEntry& other) = delete;

            // This memory needs to be managed outside of this struct
            u8*     Buffer;
            size_t  ByteOffset;
            size_t  CurrentSize;
        };

        // Create some kind of bug buffer to store all compoments to
        EMap<size_t, EComponentStorageEntry*>     fComponentStorage;
        EMap<EObject*, EVector<EComponent*>>      fComponent_Object_Storage;

        
        size_t                                           fInitialSize;
    public:
        /**
         * @param initialSize : The default amount of components to store. If size is reached we will allocate new 50 memory units. 
         */
        EComponentHandler(size_t initialSize = 100);
        ~EComponentHandler();

        template <typename T>
        auto CreateComponent(EObject* object)
        -> decltype (T::AttachedObject, (T*)nullptr)
        {
            T* result = (T*) CreateComponentIntern(typeid(T), sizeof(T), object);
            new (result) T;
            result->AttachedObject = object;
            return result;
        }

        template <typename T>
        auto GetComponent(EObject* object)
        -> decltype (T::AttachedObject, (T*)nullptr)
        {
            for (T* comp : GetAllComponents<T>())
            {
                if (comp->AttachedObject == object)
                {
                    return comp;
                }
            }
            return nullptr;
        }

        template <typename T>
        auto GetAllComponents()
        -> decltype (T::AttachedObject, EVector<T*>())
        {
            EComponentStorageEntry* storage = GetComponentStorage(typeid(T));
            EVector<T*> result;
            if (!storage) { return result; }


            for (size_t index = 0; index < storage->ByteOffset - sizeof(T); index += sizeof(T))
            {
                result.push_back((T*)storage->Buffer[index]);
            }
            return result;
        }

        EVector<EComponent*> GetAllComponents(EObject* object)
        {
            return GetComponentStorage(object);
        }

    private:
        void* CreateComponentIntern(const std::type_info& type, size_t singleMemorySize, EObject* object);
        EComponentStorageEntry* GetComponentStorage(const std::type_info& type);
        EVector<EComponent*> GetComponentStorage(EObject* object);
    };

}