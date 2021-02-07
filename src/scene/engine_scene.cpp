#include "Engine.h"

using namespace Engine;



EObjectReference::EObjectReference(const EString& refName) 
    : EBaseProperty(refName)
{
    fObject = new EObject(entt::null, nullptr);
}

EObjectReference::~EObjectReference() 
{
    delete fObject;
}

void EObjectReference::SetValue(EObject object) 
{
    if (*fObject == object) { return; }

    for (const auto& cb : fBeforeChangeCallbacks) { cb.second(); }

    fObject->Set(object);

    for (const auto& cb : fAfterChangeCallbacks) { cb.second(); }
}

EObject EObjectReference::GetValue() 
{
    return *fObject;
}

void EObjectReference::OnFromJsObject(const EJson& ref) 
{
    if (fObject && JSHelper::HasParam(ref, GetPropertyName()))
    {
        fObject->FromJsObject(ref[GetPropertyName()]);
    }
}

void EObjectReference::OnSetJsObject(EJson& ref) const
{
    if (JSHelper::HasParam(ref, GetPropertyName()))
    {
        if (ref[GetPropertyName()].size() > 0)
        {
            // Get by uuid or something
        }
        else
        {
            fObject->Set(entt::null, nullptr);
        }
    }
}






EScene::EScene(const EString& name)
    : fName("Name", name), 
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

EObjectReference& EScene::GetSelectedObject() 
{
    return fSelectedObject;
}

void EScene::SetJsObject(EJson& json)
{
    fName.SetJsObject(json);
    EJson& objectArray = json["Objects"] = EJson::array();
    ForEachObject([&objectArray](EObject object){
        object.SetJsObject(objectArray.back());
    });
}

void EScene::FromJsObject(const EJson& json) 
{
    fName.FromJsObject(json);
    u32 counter = 0;
    ForEachObject([&json, &counter](EObject object) mutable {
        object.FromJsObject(json["Objects"][counter++]);
    });
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
