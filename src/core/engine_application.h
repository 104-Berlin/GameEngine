#pragma once

namespace Engine {

    class EApplication
    {
    private:
        ERef<EWindow>    fWindow;
        ERef<EScene>     fActiveScene;
        bool             fRunning;

        EExtensionManager   fExtensionManager;
        EResourceManager    fResourceManager;
        // TEMP
        ERef<ECamera>     fCamera;

        //TODO: Find a better way for this
        ERef<EPanelComponentData> fComponentPanelData;
    public:
        EApplication();
        ~EApplication();

        void Start(const ERef<EScene>& scene = nullptr);

        void Update(float delta);
        void Render();
        void RenderImGui();
        void CleanUp();

        EResourceManager& GetResourceManager();

        const ERef<EScene>& GetActiveScene() const;


        ERef<EPanelComponentData> GetComponentPanelData() const;
    private:
        void Run();
    public:
        static EApplication& gApp();
    };

}