#include "Engine.h"

using namespace Engine;




EApplication& EApplication::gApp()
{
    static EApplication app;
    return app;
}


EApplication::EApplication()
    : fActiveScene("Active Scene", nullptr), fUIRenderer(nullptr), fResourceManager(nullptr), fExtensionManager(nullptr), fUIManager(nullptr)
{
    fFrameTime = 0;
    fMainWindow = nullptr;
    fCamera = EMakeRef(ECamera, glm::perspective(30.0f, 16.0f / 9.0f, 0.1f, 1000000.0f));

    CreateMainWindow();
}

EApplication::~EApplication()
{
    if (fUIRenderer)
    {
        delete fUIRenderer;
    }
    if (fResourceManager)
    {
        delete fResourceManager;
    }
    if (fExtensionManager)
    {
        delete fExtensionManager;
    }
    if (fUIManager)
    {
        delete fUIManager;
    }
    ERenderer::CleanUp();
    glfwDestroyWindow(fMainWindow);
    glfwTerminate();
}

void EApplication::Start(const ERef<EScene>& scene)
{

    RegisterInternComponents();

    fExtensionManager->LoadPluginFolder();
    fResourceManager->LoadAllFromFolder(EFolder(EBaseFolder::RES));



    fActiveScene = scene;

    if (!fActiveScene)
    {
        fActiveScene = EMakeRef(EScene, "Scene 1");
    }


    // First register intern panels bevore set up main menu, so the view menu is up to data
    RegisterInternPanels();

    // After regsiter intern panels
    SetUpMainMenuBar();


    
    
    fRunning = true;
    Run();
}

void EApplication::Run()
{
    if (!fMainWindow) 
    {
        std::cout << "No main windows created at starting!" << std::endl;
        return;
    }
    
    ETimer timer;
    while (fRunning)
    {
        glfwPollEvents();

        // Store this global in the app i think
        fFrameTime = timer.Reset();
        fEventDispatcher.Update();
        for (ERef<EUIPanel> panel : fUIManager->GetPanels())
        {
            panel->UpdateEvents();
        }
        fMainMenuBar.UpdateEvents();
        
        Update(fFrameTime);

        Render();

        RenderImGui();
        ERenderer::WaitAndRender();

        glfwMakeContextCurrent(fMainWindow);
        glfwSwapBuffers(fMainWindow);

        fRunning = !(bool)glfwWindowShouldClose(fMainWindow);
    }
}

void EApplication::SetUpMainMenuBar() 
{
    ApplicationPanels::CreateDefaultMainMenuBar();
}

void EApplication::RegisterInternComponents() 
{
    EPanelComponentData::data().RegisterComponent<ENameComponent>("Name");
    EPanelComponentData::data().RegisterComponent<ETransformComponent>("Transform Component");
    EPanelComponentData::data().RegisterComponent<EMeshComponent>("Mesh");
    EPanelComponentData::data().RegisterComponent<TestComponent>("Test Component");
    EPanelComponentData::data().RegisterComponent<ECameraComponent>("Camera Component");
}

void EApplication::RegisterInternPanels() 
{
    
    ApplicationPanels::CreateDefaultApplicationPanels();

}

void EApplication::CreateMainWindow() 
{
    // Create window with graphics context
    if (!glfwInit())
    {
        std::cout << "Could not init glfw" << std::endl;
        return;
    }

#ifdef __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif



    fMainWindow = glfwCreateWindow(1280, 720, "ENGINE", NULL, NULL);
    if (!fMainWindow)
    {
        std::cout << "Could not create main windows!" << std::endl;
        return;
    }
    glfwMakeContextCurrent(fMainWindow);
    glfwSwapInterval(1); // Enable vsync

    ERenderer::Init();
    ERenderContext::Create(fMainWindow);
    fUIRenderer = new EUIRenderer();
    fUIRenderer->Init(fMainWindow);

    fResourceManager = new EResourceManager();
    fExtensionManager = new EExtensionManager();
    fUIManager = new EUIManager();
}

void EApplication::Update(float delta)
{
    if (fActiveScene)
    {
        fActiveScene->Update(delta);
    }
}

void EApplication::Render()
{
    if (fActiveScene)
    {
        fActiveScene->Render();
    }
}

void EApplication::RenderImGui()
{
    if (!fUIRenderer->IsInitialized()) { return; }
    int width = 0;
    int height = 0;

    glfwGetFramebufferSize(fMainWindow, &width, &height);

    IN_RENDER2(width, height, {
        glCall(glViewport(0, 0, width, height));
    })

    
    fUIRenderer->Begin();
    //UI::NewFrame();

    fMainMenuBar.Render();
    //RenderResourcePanel(*fResourceManager);

    for (ERef<EUIPanel> panel : fUIManager->GetPanels())
    {
        panel->Render();
    }




    if (fActiveScene)
    {
        fActiveScene->RenderUI();
    }
    
    fUIRenderer->Render();
    //UI::Render();
}

void EApplication::CleanUp() 
{
    ERenderer::CleanUp();
}

double EApplication::GetFrameTime() const
{
    return fFrameTime;
}

EResourceManager& EApplication::GetResourceManager() 
{
    return *fResourceManager;
}

EUIManager& EApplication::GetUIManager() 
{
    return *fUIManager;
}

EUIMainMenuBar& EApplication::GetMainMenuBar() 
{
    return fMainMenuBar;
}

ERef<EUIPanel> EApplication::GetPanelByName(const EString& name) 
{
    EVector<ERef<EUIPanel>> panels = fUIManager->GetPanels();
    for (size_t i = 0; i < panels.size(); i++)
    {
        if (panels[i]->GetPanelTitle().compare(name) == 0)
        {
            return panels[i];
        }
    }
    return nullptr;
}

ImGuiContext* EApplication::GetMainImGuiContext() const
{
    return fUIRenderer->GetImGuiContext();
}

EObjectProperty<EScene>& EApplication::GetActiveScene()
{
    return fActiveScene;
}