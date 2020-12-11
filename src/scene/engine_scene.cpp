#include "Engine.h"

using namespace Engine;

EScene::EScene(const EString& name)
    : EObject(name), fActiveCamera(nullptr), fSceneFrameBuffer(nullptr), 
        fEntryObject(this, "SceneEntry"),
        fSelectedObject(this, "SelectedObject")
{
    fNameField = new char[256];
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

    if (fEntryObject.GetValue())
    {
        ImGui::Begin("SceneTree##SCENETREE");


        ESceneObject* obj = fEntryObject.GetValue();
        while (obj)
        {
            RenderUITreeNode(obj);
            obj = obj->GetNext();
        }
        ImGui::End();
    }


    ImGui::Begin("Object Properties##OIP");
    if (fSelectedObject.GetValue())
    {
        RenderUIOIP(fSelectedObject.GetValue());
    }
    ImGui::End();
}

void EScene::RenderUITreeNode(ESceneObject* object)
{
    if (!object) { return; }

    bool showNode = false;
    if (object->GetChild())
    {
        showNode = ImGui::TreeNodeEx((object->GetName() + "##" + object->GetUuid().ToString()).c_str(), ImGuiTreeNodeFlags_DefaultOpen);
    }
    else 
    {
        ImGui::Selectable(object->GetName().c_str());
    }

    if (ImGui::IsItemClicked())
    {
        fSelectedObject.SetValue(object);
        strcpy(fNameField, object->GetName().c_str());
    }

    if (showNode)
    {
        ESceneObject* temp = object->GetChild();
        while (temp)
        {
            if (temp->GetChild())
            {
                ImGui::Indent();
            }
            RenderUITreeNode(temp);
            if (temp->GetChild())
            {
                ImGui::Unindent();
            }

            temp = temp->GetNext();
        }
        ImGui::TreePop();
    }
}

void EScene::RenderUIOIP(ESceneObject* sceneObject)
{
    if (ImGui::InputText("Name", fNameField, 256, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        sceneObject->SetName(fNameField);
    }
}

void EScene::OnUpdate(float delta)
{
    EObject::OnUpdate(delta);
}


ESceneObject* EScene::CreateNewObject(const EString& name)
{
    ESceneObject* newObject = new ESceneObject(name.empty() ? "Scene Object" : name);
    fAllObjects[newObject->GetUuid()] = newObject;

    if (!fEntryObject.GetValue())
    {
        fEntryObject.SetValue(newObject);
    }
    else
    {
        ESceneObject* temp = fEntryObject.GetValue();
        while (temp->GetNext())
        {
            temp = temp->GetNext();
        }

        temp->SetNext(newObject);
        newObject->SetPrev(temp);
        newObject->SetParent(temp->GetParent());
    }


    return newObject;
}

void EScene::DeleteObject(const EUUID& uuid)
{
    ESceneObject* object = GetByUuid(uuid);
    if (object)
    {
        fAllObjects.erase(uuid);
        delete object;
    }
}

ESceneObject* EScene::GetByUuid(const EUUID& uuid)
{
    return fAllObjects[uuid];
}

void EScene::SetActiveCamera(ECamera* camera)
{
    fActiveCamera = camera;
}

ECamera* EScene::GetActiveCamera() const
{
    return fActiveCamera;
}
