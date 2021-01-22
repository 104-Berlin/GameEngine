#include "Engine.h"

using namespace Engine;

EApplication& EApplication::gApp()
{
    static EApplication app;
    return app;
}


EApplication::EApplication()
{
    fCamera = EMakeRef(ECamera, glm::perspective(30.0f, 16.0f / 9.0f, 0.1f, 1000000.0f));

    EWindowProp windowInit("ENGINE", 1270, 720);
    fWindow = EMakeRef(EWindow, windowInit);
}

EApplication::~EApplication()
{
}

void EApplication::Start(const ERef<EScene>& scene)
{
    fActiveScene = scene;
    // For now in edit mode
    EPanelComponentData::data().RegisterComponent<ETransformComponent>("Transform Component");
    EPanelComponentData::data().RegisterComponent<EMeshComponent>("Mesh");
    EPanelComponentData::data().RegisterComponent<TestComponent>("Test Component");
    EPanelComponentData::data().RegisterComponent<ECameraComponent>("Camera Component");


    fExtensionManager.LoadPluginFolder();
    fResourceManager.LoadAllFromFolder(EFolder(EBaseFolder::RES));


    if (!fActiveScene)
    {
        fActiveScene = EMakeRef(EScene, "Scene 1");
    }
    
    fRunning = true;
    Run();
}

void EApplication::Run()
{
    float delta = 0.0f;
    ETimer timer;
    while (fRunning)
    {
        delta = timer.Reset();
        Update(delta);

        Render();

        RenderImGui();

        ERenderer::WaitAndRender();
        fWindow->Update();

        fRunning = !fWindow->IsClosed();
    }
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
    int width = 0;
    int height = 0;

    glfwGetFramebufferSize(fWindow->GetNativeWindow(), &width, &height);

    IN_RENDER2(width, height, {
        glCall(glViewport(0, 0, width, height));
    })


    UI::NewFrame();


    IN_RENDER_S({

        RenderResourcePanel(self->fResourceManager);
        

        if (self->fActiveScene)
        {
            self->fActiveScene->RenderUI();
        }
    })

    UI::Render();
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
            ImGui::SetDragDropPayload("_RESOURCEDRAG", res.first.c_str(), strlen(res.first.c_str()));

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
