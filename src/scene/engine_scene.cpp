#include "Engine.h"

using namespace Engine;



EScene::EScene(const EString& name)
    : fName(name), 
    fViewPortWidth(1270), 
    fViewPortHeight(720), 
    fSelectedObject("SelectedObject")
{
    //fSceneFrameBuffer = EFrameBuffer::Create(fViewPortWidth, fViewPortHeight, EFramebufferFormat::RGBA8);		
}

EScene::~EScene()
{
}

void EScene::Render()
{
    auto cameraView = fRegistry.view<ECameraComponent, ETransformComponent>();
    if (cameraView.empty()) { /*std::cout << "No active camera set to scene!" << std::endl;*/ return; }
    
    // Render components

    for (auto& entry : cameraView)
    {
        ECameraComponent& camComp = fRegistry.get<ECameraComponent>(entry);
        ETransformComponent& cameraTransform = fRegistry.get<ETransformComponent>(entry);
        if (camComp.Active)
        {
            //fSceneFrameBuffer->Resize(fViewPortWidth, fViewPortHeight);		
            //fSceneFrameBuffer->Bind();		

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
    //fSceneFrameBuffer->Unbind();
}

void EScene::RenderUI()
{
    
}

void EScene::Update(float delta)
{
}

EProperty<EObject>& EScene::GetSelectedObject() 
{
    return fSelectedObject;
}

void EScene::ForEachObject(ObjectCallback fn) 
{
    fRegistry.each([this, fn](EEntity entity){
        fn(EObject(entity, this));
    });
}

EObject EScene::CreateObject()
{
    EEntity handle = fRegistry.create();
    EObject object(handle, this);
    object.AddComponent<EUUIDComponent>(EUUID().CreateNew());
    object.AddComponent<ETransformComponent>();
    object.AddComponent<ENameComponent>("Empty Object");
    return object;
}
