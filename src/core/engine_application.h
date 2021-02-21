#pragma once

namespace Engine {

    class EApplication
    {
    private:
        GLFWwindow*                 fMainWindow;
        EObjectProperty<EScene>     fActiveScene;
        bool                        fRunning;
        double                      fFrameTime;

        EExtensionManager*          fExtensionManager;
        EResourceManager*           fResourceManager;
        EUIManager*                 fUIManager;

        EUIRenderer*                fUIRenderer;

        EEventDispatcher            fEventDispatcher;
        // TEMP
        ERef<EUIMainMenuBar>      fMainMenuBar;
        ERef<ECamera>     fCamera;
        EObject             fMeshObject;
    public:
        EApplication();
        ~EApplication();

        void Start(const ERef<EScene>& scene = nullptr);

        void Update(float delta);
        void Render();
        void CleanUp();
        
        double                      GetFrameTime() const;
        EResourceManager&           GetResourceManager();
        EUIManager&                 GetUIManager();
        EUIRenderer&                GetUIRenderer();
        ERef<EUIMainMenuBar>        GetMainMenuBar();
        ERef<EUIPanel>              GetPanelByName(const EString& name);


        EObjectProperty<EScene>&    GetActiveScene();
        void                        SetActiveScene(ERef<EScene> scene);

        void                        ResetImGuiContext();

        template <typename T, typename... Args>
        void QueueEvent(Args &&... args)
        {
            fEventDispatcher.Enqueue<T>(std::forward<Args>(args)...);
        }
    private:
        void Run();

        void SetUpMainMenuBar();
        void RegisterInternComponents();
        void RegisterInternPanels();

        void CreateMainWindow();

        void LoadDefaultMeshes();

        void TestRendering();
    public:
        static EApplication& gApp();
    };

}
