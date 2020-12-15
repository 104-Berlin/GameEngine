#pragma once

namespace Engine {

    class EScene
    {
    private:
        EString                             fName;
        ERef<ECamera>                       fActiveCamera;


        // TEMP
        ERef<EFrameBuffer>                  fSceneFrameBuffer;

    public:
        EScene(const EString& name);
        ~EScene();

        void SetActiveCamera(const ERef<ECamera>& camera);
        const ERef<ECamera>& GetActiveCamera() const;

        void Render();
        void RenderUI();
        void Update(float delta);
    public:

    };

}