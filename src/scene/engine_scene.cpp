#include "Engine.h"

using namespace Engine;

EScene::EScene(const EString& name)
    : EObject(name), fActiveCamera(nullptr), fSceneFrameBuffer(nullptr)
{

}

EScene::~EScene()
{
    if (fSceneFrameBuffer)
    {
        delete fSceneFrameBuffer;
    }
}

void EScene::OnRender()
{
    EObject::OnRender();
    if (!fActiveCamera) { std::cout << "No active camera set to scene!" << std::endl; return; }

    //fSceneFrameBuffer->Bind();

    
}

void EScene::OnRenderUI()
{
    EObject::OnRenderUI();
    if (!fActiveCamera)
    {
        ImGui::Begin("No Camera##NOCAM");
        ImGui::Text("No active camera set to scene \"%s\"\n", GetName().c_str());
        ImGui::End();
    }

}

void EScene::OnUpdate(float delta)
{
    EObject::OnUpdate(delta);
}

void EScene::SetActiveCamera(ECamera* camera)
{
    fActiveCamera = camera;
}