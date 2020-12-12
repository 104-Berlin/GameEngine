#pragma once

namespace Engine {


    class EComponentHandler
    {
    private:

        // Create some kind of bug buffer to store all compoments to
        EMap<size_t, EVector<EComponent*>>     fComponentStorage;
        EMap<EObject*, EVector<EComponent*>>      fComponent_Object_Storage;
        
        size_t                                           fInitialSize;
    public:
        /**
         * @param initialSize : The default amount of components to store. If size is reached we will allocate new 50 memory units. 
         */
        EComponentHandler(size_t initialSize = 100);
        ~EComponentHandler();

        void Render();
        void Update(float delta);
        void RenderUI();

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
            return  GetComponentStorage(typeid(T));
        }

        EVector<EComponent*> GetAllComponents(EObject* object)
        {
            return GetComponentStorage(object);
        }

    private:
        void* CreateComponentIntern(const std::type_info& type, size_t singleMemorySize, EObject* object);
        EVector<EComponent*> GetComponentStorage(const std::type_info& type);
        EVector<EComponent*> GetComponentStorage(EObject* object);
    };

}