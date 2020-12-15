#include "Engine.h"

using namespace Engine;

EScene::EScene(const EString& name)
    : fActiveCamera(nullptr), fSceneFrameBuffer(nullptr), fName(name)

{
}

EScene::~EScene()
{
}

void EScene::Render()
{
    if (!fActiveCamera) { std::cout << "No active camera set to scene!" << std::endl; return; }

    if (!fSceneFrameBuffer)
    {
        fSceneFrameBuffer = EFrameBuffer::Create(1270, 720, EFramebufferFormat::RGBA8);
    }

    fSceneFrameBuffer->Bind();
    ERenderContext::s_Instance->SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});
    ERenderContext::s_Instance->Clear();

    // Render components

    fSceneFrameBuffer->Unbind();
}

void EScene::RenderUI()
{
    if (!fActiveCamera)
    {
        ImGui::Begin("No Camera##NOCAM");
        ImGui::Text("No active camera set to scene \"%s\"\n", fName.c_str());
        ImGui::End();
    }

    //fActiveCamera->UpdateImGui();

    ImGui::Begin("SceneView##SCENEVIEW");
    // Render frame buffer
    auto viewportSize = ImGui::GetContentRegionAvail();
    fSceneFrameBuffer->Resize(viewportSize.x, viewportSize.y);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fSceneFrameBuffer->GetColorAttachment());
    ImGui::Image((void*)(u64)fSceneFrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });
    ImGui::End();

    // Render all objects for now
    ImGui::Begin("SceneTree");
    fRegistry.each([this](EEntity handle)
    {
        EObject object(handle, this);
        if (object.HasComponent<ENameComponent>())
        {
            ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
            ImGui::Selectable(nameComponent.Name.c_str());
        }
        else
        {
            ImGui::Selectable("Unknown");
        }
    });
    ImGui::End();
}

void EScene::Update(float delta)
{
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    return object;
}

void EScene::SetActiveCamera(const ERef<ECamera>& camera)
{
    fActiveCamera = camera;
}

const ERef<ECamera>& EScene::GetActiveCamera() const
{
    return fActiveCamera;
}
