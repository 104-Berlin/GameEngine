#pragma once

namespace Engine {

    class EApplication
    {
    private:
        EWindow*    fWindow;
        EScene*     fActiveScene;
        bool        fRunning;

        // TEMP
        ECamera     fCamera;
    public:
        EApplication();
        ~EApplication();

        void Start(EScene* scene = nullptr);

        void Update(float delta);
        void Render();
        void RenderImGui();

        EScene* GetActiveScene();
    private:
        void Run();
    public:
        static EApplication& gApp();
    };

}