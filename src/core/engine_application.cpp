#include "Engine.h"

using namespace Engine;


#define PANEL_NAME_COMPONENT "Components"
#define PANEL_NAME_SCENETREE "Scene Tree"
#define PANEL_NAME_RESOURCES "Resources"



EApplication& EApplication::gApp()
{
    static EApplication app;
    return app;
}


EApplication::EApplication()
    : fActiveScene("Active Scene", nullptr), fUIRenderer(nullptr), fResourceManager(nullptr), fExtensionManager(nullptr), fUIManager(nullptr)
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
    for (ERef<EUIPanel> panel : fUIManager->GetPanels())
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
    ERef<EUIPanel> componentsPanel = EMakeRef(EUIPanel, PANEL_NAME_COMPONENT);
    ERef<EUIField> panelsContainer = componentsPanel->AddChild(EMakeRef(EUIContainer, "Components Container"));
    panelsContainer->SetUpdateFunction([this](ERef<EUIField> panel){
        panel->ClearChildren();
        EObject object = this->GetActiveScene()->GetSelectedObject().GetValue();
        if (!object) { return; }
        for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
        {
            if (compDsc->Has(object))
            {
                panel->AddChild(compDsc->CreateUIField(object));
            }
        }}
    );

    ERef<EUIField> componentsContextMenu = componentsPanel->AddChild(EMakeRef(EUIContextMenu));
    for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
    {
        ERef<EUIMenuItem> menuItem = EMakeRef(EUIMenuItem, compDsc->Name);
        menuItem->SetOnClick([this, compDsc](){
            EObject object = this->GetActiveScene()->GetSelectedObject().GetValue();
            if (object)
            {
                compDsc->Create(object);
                ERef<EUIPanel> componentPanel = this->GetPanelByName(PANEL_NAME_COMPONENT);
                if (componentPanel)
                {
                    componentPanel->Update();
                }
            }
        });
        componentsContextMenu->AddChild(menuItem);
    }

    fUIManager->RegisterPanel(componentsPanel);

    // ---------------------------------------------------------------------------------
    ERef<EUIPanel> sceneViewPanel = EMakeRef(EUIPanel, PANEL_NAME_SCENETREE);
    ERef<EUIField> objectContainer = sceneViewPanel->AddChild(EMakeRef(EUIContainer, "ObjectContainer"));

    objectContainer->SetUpdateFunction([this](ERef<EUIField> sceneList){
        sceneList->ClearChildren();
        this->GetActiveScene()->ForEachObject([this, sceneList](EObject object){
            if (object.HasComponent<ENameComponent>())
            {
                ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
                nameComponent.Name.AddEventAfterChange((intptr_t)this, [sceneList](){
                    sceneList->Update();
                });

                ERef<EUISelectable> selectable = EMakeRef(EUISelectable, nameComponent.Name);
                selectable->SetOnClick([this, object](){
                    this->fActiveScene->GetSelectedObject().SetValue(object); 
                    ERef<EUIPanel> componentsPanel = this->GetPanelByName(PANEL_NAME_COMPONENT);
                    if (componentsPanel)
                    {
                        componentsPanel->Update();
                    }
                });
                sceneList->AddChild(selectable);
            }
        });
    });

    fActiveScene.AddEventAfterChange((intptr_t)this, [this](){
        ERef<EUIPanel> componentPanel = this->GetPanelByName(PANEL_NAME_COMPONENT);
        ERef<EUIPanel> sceneTreePanel = this->GetPanelByName(PANEL_NAME_SCENETREE);
        if (componentPanel) { componentPanel->Update(); }
        if (sceneTreePanel) { sceneTreePanel->Update(); }
    });

    // Context Menu
    ERef<EUIField> contextMenu = sceneViewPanel->AddChild(EMakeRef(EUIContextMenu));
    ERef<EUIMenuItem> addObjectItem = EMakeRef(EUIMenuItem, "Add Object");
    addObjectItem->SetOnClick([this](){
        this->fActiveScene->CreateObject();
        ERef<EUIPanel> sceneTreePanel = this->GetPanelByName(PANEL_NAME_SCENETREE);
        if (sceneTreePanel) { sceneTreePanel->Update(); }
    });
    contextMenu->AddChild(addObjectItem);

    fUIManager->RegisterPanel(sceneViewPanel);



    // ------------------------------------
    // Resource Panel

    ERef<EUIPanel> resourcePanel = EMakeRef(EUIPanel, PANEL_NAME_RESOURCES);
    resourcePanel->SetUpdateFunction([this](ERef<EUIField> uiField){
        uiField->ClearChildren();
        for (auto& res : *fResourceManager)
        {
            ERef<EUISelectable> selectable = EMakeRef(EUISelectable, res.first);
            EDragData data;
            data.Type = "_RESOURCEDRAG";
            data.Buffer = (void*)res.first.c_str();
            data.Size = res.first.length() + 1;
            selectable->SetDragData(data);
            uiField->AddChild(selectable);
        }
    });
    

    fResourceManager->SetOnWorkFinished([this](){
        ERef<EUIPanel> resourcePanel = this->GetPanelByName(PANEL_NAME_RESOURCES);
        if (resourcePanel)
        {
            resourcePanel->Update();
        }
    });

    fUIManager->RegisterPanel(resourcePanel);

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

EResourceManager& EApplication::GetResourceManager() 
{
    return *fResourceManager;
}

EUIManager& EApplication::GetUIManager() 
{
    return *fUIManager;
}

ERef<EUIPanel> EApplication::GetPanelByName(const EString& name) 
{
    EVector<ERef<EUIPanel>> panels = fUIManager->GetPanels();
    for (size_t i = 0; i < panels.size(); i++)
    {
        if (panels[i]->GetDisplayName().compare(name) == 0)
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

ERef<EScene> EApplication::GetActiveScene() const
{
    return fActiveScene.GetValue();
}