#pragma once

namespace Engine {

    class EScene
    {
    private:
        EString                             fName;
        ERef<ECamera>                       fActiveCamera;


        // TEMP
        ERef<EFrameBuffer>                  fSceneFrameBuffer;

        // Entities
        entt::registry                      fRegistry;
    public:
        EScene(const EString& name);
        ~EScene();

        void SetActiveCamera(const ERef<ECamera>& camera);
        const ERef<ECamera>& GetActiveCamera() const;

        EObject CreateObject();

        void Render();
        void RenderUI();
        void Update(float delta);
    public:
        friend class EObject;
    };

}