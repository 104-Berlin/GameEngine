#pragma once

namespace Engine {

    class EApplication
    {
    private:
        ERef<EWindow>    fWindow;
        ERef<EScene>     fActiveScene;
        bool             fRunning;

        EResourceManager fResourceManager;
        // TEMP
        ERef<ECamera>     fCamera;
    public:
        EApplication();
        ~EApplication();

        void Start(const ERef<EScene>& scene = nullptr);

        void Update(float delta);
        void Render();
        void RenderImGui();
        void CleanUp();

        const ERef<EScene>& GetActiveScene() const;
    private:
        void Run();
    public:
        static EApplication& gApp();
    };

}