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
    


    // Render components

    for (auto& entry : cameraView)
    {
        ECameraComponent& camComp = fRegistry.get<ECameraComponent>(entry);
        ETransformComponent& cameraTransform = fRegistry.get<ETransformComponent>(entry);
        if (camComp.Active)
        {
            //camComp.FrameBuffer->Resize(fViewPortWidth, fViewPortHeight);
            camComp.FrameBuffer->Bind();

            
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
            camComp.FrameBuffer->Unbind();
            break;
        }
    }
}

void EScene::RenderUI()
{




    for (EEntity handle : fRegistry.view<ECameraComponent>())
    {
        ECameraComponent& cameraComponent = fRegistry.get<ECameraComponent>(handle);

        if (cameraComponent.Active)
        {
            EString name = "Scene View##" + std::to_string((int)handle);
            ImGui::Begin(name.c_str());
            ImGui::Separator();

            // Render frame buffer
            auto viewportSize = ImGui::GetContentRegionAvail();
            fViewPortWidth = viewportSize.x;
            fViewPortHeight = viewportSize.y;


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cameraComponent.FrameBuffer->GetColorAttachment());
            ImGui::Image((void*)(u64)cameraComponent.FrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });

            if (cameraComponent.Active)
            {
                ((ERef<ECamera>) cameraComponent.Camera)->UpdateImGui();
            }
            ImGui::End();
        }
    }


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
    for (EEntity entity : fRegistry.view<ECameraComponent>())
    {
        ECameraComponent& cameraComponent = fRegistry.get<ECameraComponent>(entity);
        cameraComponent.Camera->SetProjectionMatrix(GetProjectionMatrix(ECameraComponent::CameraMode::PERSPECTIVE, cameraComponent.FrameBuffer->GetWidth(), cameraComponent.FrameBuffer->GetHeight()));
    }
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    object.AddComponent<ETransformComponent>();
    return object;
}
