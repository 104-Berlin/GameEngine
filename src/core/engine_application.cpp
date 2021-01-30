#include "Engine.h"

using namespace Engine;

EApplication& EApplication::gApp()
{
    static EApplication app;
    return app;
}


EApplication::EApplication()
{
    fMainWindow = nullptr;
    fCamera = EMakeRef(ECamera, glm::perspective(30.0f, 16.0f / 9.0f, 0.1f, 1000000.0f));

    CreateMainWindow();
}

EApplication::~EApplication()
{
    ERenderer::CleanUp();
    glfwDestroyWindow(fMainWindow);
    glfwTerminate();
}

void EApplication::Start(const ERef<EScene>& scene)
{
    fActiveScene = scene;

    RegisterInternComponents();

    fExtensionManager.LoadPluginFolder();
    fResourceManager.LoadAllFromFolder(EFolder(EBaseFolder::RES));

    SetUpMainMenuBar();

    if (!fActiveScene)
    {
        fActiveScene = EMakeRef(EScene, "Scene 1");
    }
    
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
    float delta = 0.0f;
    ETimer timer;
    while (fRunning)
    {
        glfwPollEvents();

        delta = timer.Reset();
        Update(delta);

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
    ERef<EUIField> fileMenu = fMainMenuBar.AddChild(EMakeRef(EMenu, "File"));
    ERef<EUIField> editMenu = fMainMenuBar.AddChild(EMakeRef(EMenu, "Edit"));
}

void EApplication::RegisterInternComponents() 
{
    EPanelComponentData::data().RegisterComponent<ENameComponent>("Name");
    EPanelComponentData::data().RegisterComponent<ETransformComponent>("Transform Component");
    EPanelComponentData::data().RegisterComponent<EMeshComponent>("Mesh");
    EPanelComponentData::data().RegisterComponent<TestComponent>("Test Component");
    EPanelComponentData::data().RegisterComponent<ECameraComponent>("Camera Component");
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
    fUIRenderer.Init(fMainWindow);
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
    if (!fUIRenderer.IsInitialized()) { return; }
    int width = 0;
    int height = 0;

    glfwGetFramebufferSize(fMainWindow, &width, &height);

    IN_RENDER2(width, height, {
        glCall(glViewport(0, 0, width, height));
    })

    
    fUIRenderer.Begin();
    //UI::NewFrame();

    fMainMenuBar.Render();
    RenderResourcePanel(fResourceManager);

    if (fActiveScene)
    {
        fActiveScene->RenderUI();
    }
    
    fUIRenderer.Render();
    //UI::Render();
}

void EApplication::CleanUp() 
{
    ERenderer::CleanUp();
}

EResourceManager& EApplication::GetResourceManager() 
{
    return fResourceManager;
}

const ERef<EScene>& EApplication::GetActiveScene() const
{
    return fActiveScene;
}




void EApplication::RenderResourcePanel(EResourceManager& resourceManager)
{
    ImGui::Begin("Resource Manager##RESOURCEMANAGER");
    for (auto& res : resourceManager)
    {
        ImGui::Selectable(res.first.c_str(), false);
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("_RESOURCEDRAG", res.first.c_str(), res.first.length() + 1);

            EString resourceType = EResourceManager::GetResourceTypeFromFile(res.first);
            if (resourceType == typeid(ETexture2D).name())
            {
                ERef<ETexture2D> texture = std::static_pointer_cast<ETexture2D>(res.second);
                // This should not be here
                //glBindTexture(GL_TEXTURE_2D, );
                ImGui::Image((void*)(u64)texture->GetRendererID(), ImVec2(100, 100));
            }
            
            ImGui::EndDragDropSource();
        }
    }
    ImGui::End();
}
