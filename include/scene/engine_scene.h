#pragma once

namespace Engine {

    class EScene : public EObject
    {
    private:
        ESceneObject*   fEntryObject;
        ECamera*        fActiveCamera;

        // TEMP
        EFrameBuffer*   fSceneFrameBuffer;
    public:
        EScene(const EString& name);
        ~EScene();

        void AddObject(ESceneObject* object, ESceneObject* parent);
        void RemoveObject(ESceneObject* object);

        void SetActiveCamera(ECamera* camera);

        virtual void OnRender() override;
        virtual void OnRenderUI() override;
        virtual void OnUpdate(float delta) override;
    };

}