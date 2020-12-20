#include "Engine.h"

using namespace Engine;



EScene::EScene(const EString& name)
    : fActiveCamera(nullptr), fSceneFrameBuffer(nullptr), fName(name), fViewPortWidth(1270), fViewPortHeight(720), fSelectionContext(entt::null)

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
        fSceneFrameBuffer = EFrameBuffer::Create(fViewPortWidth, fViewPortHeight, EFramebufferFormat::RGBA8);
    }
    fSceneFrameBuffer->Resize(fViewPortWidth, fViewPortHeight);

    fSceneFrameBuffer->Bind();
    
    // Render components
    ERenderer::Begin(fActiveCamera, {});
    auto view = fRegistry.group<EMeshComponent, ETransformComponent>();
    for (EEntity entity : view)
    {
        EMeshComponent meshComponent = view.get<EMeshComponent>(entity);
        ETransformComponent transformComponent = view.get<ETransformComponent>(entity);
        if (meshComponent.Mesh)
        {
            ERenderer::Draw(meshComponent.Mesh->fVertexArray, transformComponent);
        }

    }
    ERenderer::End();

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


    ImGui::Begin("SceneView##SCENEVIEW");
    // Render frame buffer
    auto viewportSize = ImGui::GetContentRegionAvail();
    fViewPortWidth = viewportSize.x;
    fViewPortHeight = viewportSize.y;
    
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fSceneFrameBuffer->GetColorAttachment());
    ImGui::Image((void*)(u64)fSceneFrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });
    fActiveCamera->UpdateImGui();

    glBindTexture(GL_TEXTURE_2D, 0);
    ImGui::End();

    // Render all objects for now
    ImGui::Begin("SceneTree");
    fRegistry.each([this](EEntity handle)
    {
        EObject object(handle, this);
        if (object.HasComponent<ENameComponent>())
        {
            ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
            if (ImGui::Selectable(nameComponent.Name.c_str()))
            {
                this->fSelectionContext = handle;
            }
        }
        else
        {
            ImGui::Selectable("Unknown");
        }
    });
    ImGui::End();

    
    UI::RenderComponentPanel(EObject(fSelectionContext, this));

}

void EScene::Update(float delta)
{
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    object.AddComponent<ETransformComponent>();
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
