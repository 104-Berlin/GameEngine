#include "Engine.h"

using namespace Engine;

EScene::EScene(const EString& name)
    : EObject(name), fActiveCamera(nullptr), fSceneFrameBuffer(nullptr), 
        fEntryObject(this, "SceneEntry"),
        fSelectedObject(this, "SelectedObject"),
        fComponentHandler(50)
{
    fNameField = new char[256];
}

EScene::~EScene()
{
    if (fSceneFrameBuffer)
    {
        delete fSceneFrameBuffer;
    }

    for (auto& mapEntry : fAllObjects)
    {
        delete mapEntry.second;
    }
    fAllObjects.clear();
}

void EScene::OnRender()
{
    EObject::OnRender();
    if (!fActiveCamera) { std::cout << "No active camera set to scene!" << std::endl; return; }

    if (!fSceneFrameBuffer)
    {
        fSceneFrameBuffer = EFrameBuffer::Create(1270, 720, EFramebufferFormat::RGBA8);
    }

    fSceneFrameBuffer->Bind();
    ERenderContext::s_Instance->SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});
    ERenderContext::s_Instance->Clear();

    fComponentHandler.Render();

    fSceneFrameBuffer->Unbind();
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

    ImGui::Begin("Viewport##RenderView");

    auto viewportSize = ImGui::GetContentRegionAvail();
    fSceneFrameBuffer->Resize(viewportSize.x, viewportSize.y);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fSceneFrameBuffer->GetColorAttachment());
    ImGui::Image((void*) fSceneFrameBuffer->GetColorAttachment(), viewportSize, { 0, 1 }, { 1, 0 });
    ImGui::End();
}

void EScene::RenderUITreeNode(ESceneObject* object)
{
    if (!object) { return; }

    bool showNode = false;
     
    showNode = ImGui::TreeNodeEx(object->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog);

    ImGuiDragDropFlags src_flags = 0;
    //src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
    src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
    //src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
    
    if (ImGui::BeginDragDropSource(src_flags))
    {
        if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
            ImGui::Text("Moving \"%s\"", object->GetName().c_str());
        ImGui::SetDragDropPayload("DND_DEMO_NAME", &object->GetUuid(), sizeof(EUUID));
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        //target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
        //target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", target_flags))
        {
            EUUID move_from = *(EUUID*)payload->Data;
            ESceneObject* moveFromObject = GetByUuid(move_from);
            if (moveFromObject)
            {
                object->SetNewChild(moveFromObject);
            }
        }
        ImGui::EndDragDropTarget();
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

    EVector<EComponent*> components = GetObjectComponents(sceneObject);
    for (EComponent* comp : components)
    {
        if (ImGui::CollapsingHeader(comp->GetName().c_str()))
        {
            ImGui::Button("Button");
        }
    }
}

void EScene::OnUpdate(float delta)
{
    EObject::OnUpdate(delta);
}

void EScene::SetEntryObject(const EUUID& uuid)
{
    ESceneObject* object = GetByUuid(uuid);
    if (object)
    {
        fEntryObject.SetValue(object);
    }
}

ESceneObject* EScene::CreateNewObject(const EString& name)
{
    ESceneObject* newObject = new ESceneObject(name.empty() ? "Scene Object" : name);
    newObject->SetScene(this);
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

EResource* EScene::GetResource(const EUUID& uuid)
{
    return fLoadedReources[uuid];
}

bool EScene::LoadResource(EResource* resource)
{
    EFile tempFile(resource->GetFilePath());
    
    if (!tempFile.Exist()) { std::cout << "Cant load resource! Wrong path: " << resource->GetFilePath() << std::endl; return false; }

    bool result = false;

    if (resource->GetFilePath().empty() ||tempFile.GetFileExtension().compare("er"))
    {
        result = resource->Load();
    }
    else
    {
        result = resource->Import();
    }
    fLoadedReources[resource->GetUuid()] = resource;
    return result;
}

void EScene::SetActiveCamera(ECamera* camera)
{
    fActiveCamera = camera;
}

ECamera* EScene::GetActiveCamera() const
{
    return fActiveCamera;
}
