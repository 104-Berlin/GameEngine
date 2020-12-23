#include "Engine.h"

using namespace Engine;



EScene::EScene(const EString& name)
    : fSceneFrameBuffer(nullptr), fName(name), fViewPortWidth(1270), fViewPortHeight(720), fSelectionContext(entt::null)

{
}

EScene::~EScene()
{
}

void EScene::Render()
{
    auto cameraView = fRegistry.view<ECameraComponent, ETransformComponent>();
    if (cameraView.empty()) { std::cout << "No active camera set to scene!" << std::endl; return; }
    


    if (!fSceneFrameBuffer)
    {
        fSceneFrameBuffer = EFrameBuffer::Create(fViewPortWidth, fViewPortHeight, EFramebufferFormat::RGBA8);
    }

    
    // Render components

    for (auto& entry : cameraView)
    {
        ECameraComponent& camComp = fRegistry.get<ECameraComponent>(entry);
        ETransformComponent& cameraTransform = fRegistry.get<ETransformComponent>(entry);
        if (camComp.Active)
        {
            fSceneFrameBuffer->Resize(fViewPortWidth, fViewPortHeight);
            fSceneFrameBuffer->Bind();

            
            ERenderer::Begin(camComp.Camera, glm::inverse((EMat4)cameraTransform), {});
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

            break;
        }
    }
    

    fSceneFrameBuffer->Unbind();
}

void EScene::RenderUI()
{
    ImGui::Begin("SceneView##SCENEVIEW");
    // Render frame buffer
    auto viewportSize = ImGui::GetContentRegionAvail();
    fViewPortWidth = viewportSize.x;
    fViewPortHeight = viewportSize.y;
    
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fSceneFrameBuffer->GetColorAttachment());
    ImGui::Image((void*)(u64)fSceneFrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });

    for (EEntity handle : fRegistry.view<ECameraComponent>())
    {
        ECameraComponent& cameraComponent = fRegistry.get<ECameraComponent>(handle);
        if (cameraComponent.Active)
        {
            ((ERef<ECamera>) cameraComponent.Camera)->UpdateImGui();
        }
    }

    ImGui::End();

    // Render all objects for now
    ImGui::Begin("SceneTree");
    fRegistry.each([this](EEntity handle)
    {
        EObject object(handle, this);
        if (object.HasComponent<ENameComponent>())
        {
            ENameComponent& nameComponent = object.GetComponent<ENameComponent>();
            if (ImGui::Selectable(nameComponent.Name.GetValue().c_str()))
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
