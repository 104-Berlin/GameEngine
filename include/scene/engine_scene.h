#pragma once

namespace Engine {

    class EScene : public EObject
    {
    private:
        EObjectProperty<ESceneObject>       fEntryObject;
        EObjectProperty<ESceneObject>       fSelectedObject;

        ECamera*                            fActiveCamera;

        // TEMP
        EFrameBuffer*                       fSceneFrameBuffer;
        char*                               fNameField;

        EMap<EUUID, ESceneObject*>          fAllObjects;
        EMap<EUUID, EResource*>             fLoadedReources;


        // Component Handler
        EComponentHandler                   fComponentHandler;
    public:
        EScene(const EString& name);
        ~EScene();

        void SetEntryObject(const EUUID& uuid);
        ESceneObject* CreateNewObject(const EString& name = "");
        void DeleteObject(const EUUID& uuid);
        ESceneObject* GetByUuid(const EUUID& uuid);

        EResource* GetResource(const EUUID& uuid);
        bool LoadResource(EResource* resource);

        void SetActiveCamera(ECamera* camera);
        ECamera* GetActiveCamera() const;

        virtual void OnRender() override;
        virtual void OnRenderUI() override;
        virtual void OnUpdate(float delta) override;
    private:
        void RenderUITreeNode(ESceneObject* sceneObject);
        void RenderUIOIP(ESceneObject* sceneObject);

    public:
        // Template functions for components

        template <typename T>
        auto CreateComponent(EObject* object)
        -> decltype (T::AttachedObject, (T*)nullptr)
        {
            return fComponentHandler.CreateComponent<T>(object);            
        }

        template <typename T>
        auto GetComponent(EObject* object)
        -> decltype (T::AttachedObject, (T*)nullptr)
        {
            return fComponentHandler.GetComponent<T>(object);
        }

        template <typename T>
        auto GetAllComponents()
        -> decltype (T::AttachedObject, EVector<T*>())
        {
            return fComponentHandler.GetAllComponents<T>();
        }
        
        EVector<EComponent*> GetObjectComponents(EObject* object)
        {
            return fComponentHandler.GetAllComponents(object);
        }
    };

}