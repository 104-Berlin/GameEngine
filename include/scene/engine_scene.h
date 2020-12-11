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
    public:
        EScene(const EString& name);
        ~EScene();

        ESceneObject* CreateNewObject(const EString& name = "");
        void DeleteObject(const EUUID& uuid);
        ESceneObject* GetByUuid(const EUUID& uuid);

        void SetActiveCamera(ECamera* camera);
        ECamera* GetActiveCamera() const;



        virtual void OnRender() override;
        virtual void OnRenderUI() override;
        virtual void OnUpdate(float delta) override;
    private:
        void RenderUITreeNode(ESceneObject* sceneObject);
        void RenderUIOIP(ESceneObject* sceneObject);
    };

}