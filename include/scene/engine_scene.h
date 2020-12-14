#pragma once

namespace Engine {

    class EScene
    {
    private:
        EString                             fName;
        ECamera*                            fActiveCamera;


        // TEMP
        EFrameBuffer*                       fSceneFrameBuffer;

    public:
        EScene(const EString& name);
        ~EScene();

        void SetActiveCamera(ECamera* camera);
        ECamera* GetActiveCamera() const;

        void Render();
        void RenderUI();
        void Update(float delta);
    public:

    };

}