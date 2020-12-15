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
    if (!fActiveScene)
    {
        fActiveScene = EMakeRef(EScene, "Scene 1");
    }
    if (!fActiveScene->GetActiveCamera())
    {
        fActiveScene->SetActiveCamera(fCamera);
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
        ERenderContext::s_Instance->Clear();
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
        glViewport(0, 0, width, height);
    })


    UI::NewFrame();


    IN_RENDER_S({

        
        if (self->fActiveScene)
        {
            self->fActiveScene->RenderUI();
        }
    })

    UI::Render();
}

const ERef<EScene>& EApplication::GetActiveScene() const
{
    return fActiveScene;
}