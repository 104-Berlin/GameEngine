#include "Engine.h"

using namespace Engine;

EApplication& EApplication::gApp()
{
    static EApplication app;
    return app;
}


EApplication::EApplication()
    : fActiveScene("Active Scene", nullptr), fUIRenderer(nullptr)
{
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
    ERenderer::CleanUp();
    glfwDestroyWindow(fMainWindow);
    glfwTerminate();
}

void EApplication::Start(const ERef<EScene>& scene)
{

    RegisterInternComponents();

    fExtensionManager.LoadPluginFolder();
    fResourceManager.LoadAllFromFolder(EFolder(EBaseFolder::RES));

    // First register intern panels bevore set up main menu, so the view menu is up to data
    RegisterInternPanels();

    // After regsiter intern panels
    SetUpMainMenuBar();


    fActiveScene = scene;

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
    ERef<EUIField> fileMenu = fMainMenuBar.AddChild(EMakeRef(EUIMenu, "File"));
    ERef<EUIField> editMenu = fMainMenuBar.AddChild(EMakeRef(EUIMenu, "Edit"));
    
    
    // View Menu
    ERef<EUIMenu> viewMenu = std::dynamic_pointer_cast<EUIMenu>(fMainMenuBar.AddChild(EMakeRef(EUIMenu, "View")));
    for (ERef<EUIPanel> panel : fUIManager.GetPanels())
    {
        ERef<EUIMenuItem> menuItem = ERef<EUIMenuItem>(new EUIMenuItem(panel->GetDisplayName()));
        menuItem->SetOnClick([panel](){
            if (panel->IsOpen())
            {
                ImGui::SetWindowFocus(panel->GetDisplayName().c_str());
            }
            else
            {
                panel->Open();
            }
        });
        viewMenu->AddChild(menuItem);
    }
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
    
    // ---------------------------------------------------------------------------------
    ERef<EUIPanel> componentsPanel = EMakeRef(EUIPanel, "Components");
    auto updateComponentsPanel = [this, componentsPanel](){
        componentsPanel->ClearChildren();
        EObject object = this->GetActiveScene()->GetSelectedObject().GetValue();
        for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
        {
            if (compDsc->Has(object))
            {
                componentsPanel->AddChild(compDsc->CreateUIField(object));
            }
        }
    };

    fUIManager.RegisterPanel(componentsPanel);

    // ---------------------------------------------------------------------------------
    ERef<EUIPanel> sceneViewPanel = EMakeRef(EUIPanel, "Scene Tree");
    ERef<EUIField> objectContainer = sceneViewPanel->AddChild(EMakeRef(EUIContainer, "ObjectContainer"));

    // Update function
    std::function<void()> updateSceneViewPanel = [this, objectContainer, &updateComponentsPanel, &updateSceneViewPanel](){
        objectContainer->ClearChildren();
        this->GetActiveScene()->ForEachObject([this, objectContainer, &updateComponentsPanel, &updateSceneViewPanel](EObject object){
            if (object.HasComponent<ENameComponent>())
            {
                ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
                nameComponent.Name.AddEventAfterChange((intptr_t)this, [&updateSceneViewPanel](){
                    updateSceneViewPanel();
                });

                ERef<EUISelectable> selectable = EMakeRef(EUISelectable, nameComponent.Name);
                selectable->SetOnClick([this, object, &updateComponentsPanel](){
                    this->fActiveScene->GetSelectedObject().SetValue(object); 
                    updateComponentsPanel();
                });
                objectContainer->AddChild(selectable);
            }
        });
    };

    fActiveScene.AddEventAfterChange((intptr_t)this, [updateSceneViewPanel](){
        updateSceneViewPanel();
    });

    // Context Menu
    ERef<EUIField> contextMenu = sceneViewPanel->AddChild(EMakeRef(EUIContextMenu));
    ERef<EUIMenuItem> addObjectItem = EMakeRef(EUIMenuItem, "Add Object");
    addObjectItem->SetOnClick([this, updateSceneViewPanel](){
        this->fActiveScene->CreateObject();
        updateSceneViewPanel();
    });
    contextMenu->AddChild(addObjectItem);

    fUIManager.RegisterPanel(sceneViewPanel);


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
    RenderResourcePanel(fResourceManager);

    for (ERef<EUIPanel> panel : fUIManager.GetPanels())
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

EResourceManager& EApplication::GetResourceManager() 
{
    return fResourceManager;
}

EUIManager& EApplication::GetUIManager() 
{
    return fUIManager;
}

ImGuiContext* EApplication::GetMainImGuiContext() const
{
    return fUIRenderer->GetImGuiContext();
}

ERef<EScene> EApplication::GetActiveScene() const
{
    return fActiveScene.GetValue();
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
