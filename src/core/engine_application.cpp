#include "Engine.h"

using namespace Engine;

EApplication::EApplication()
    : fCamera(glm::perspective(30.0f, 16.0f / 9.0f, 0.1f, 1000000.0f))
{
    fWindow = nullptr;

    EWindowProp windowInit("ENGINE", 1270, 720);
    fWindow = new EWindow(windowInit);
}

EApplication::~EApplication()
{
    if (fWindow)
    {
        delete fWindow;
    }
}

void EApplication::Start(EScene* scene)
{
    fActiveScene = scene;
    if (!fActiveScene)
    {
        fActiveScene = new EScene("Scene 1");
        fActiveScene->SetActiveCamera(&fCamera);
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
        ImGui::Begin("Hello World");
        ImGui::Text("Text");
        ImGui::End();



        /*ImGui::Begin("Viewport##RenderView");

        auto viewportSize = ImGui::GetContentRegionAvail();
        frameBuffer->Resize(viewportSize.x, viewportSize.y);
        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachment());
        ImGui::Image((void*) frameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });
        camPtr->UpdateImGui();
        ImGui::End();
        */
        if (self->fActiveScene)
        {
            self->fActiveScene->RenderUI();
        }
    })

    UI::Render();
}