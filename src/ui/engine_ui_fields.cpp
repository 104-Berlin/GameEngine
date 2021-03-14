#include "Engine.h"
#include <imgui_internal.h>

using namespace Engine;


// ----------------------------------
// Basic UI Field

EUIField::EUIField(const EString& label)
    : fLabel(label)
{
    fVisible = true;
    fId = next_ui_id();
}

EUIField::~EUIField() 
{
    fEventDispatcher.CleanUp();
}

EString EUIField::GetDisplayName() const
{
    return fLabel + "##" + std::to_string(fId);
}

void EUIField::UpdateEvents() 
{
    fEventDispatcher.Update();
    for (ERef<EUIField> child : fChildren)
    {
        child->UpdateEvents();
    }
}

void EUIField::Render() 
{
    if (!fVisible) { return; }
    if (fIsDirty && fCustomUpdateFunction)
    {
        fCustomUpdateFunction(shared_from_this());
    }
    fIsDirty = false;
    //ImGui::PushID(fId);
    if (OnRender())
    {
        for (ERef<EUIField> field : fChildren)
        {
            field->Render();
        }
    }
    if (!fDragData.Type.empty())
    {
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload(fDragData.Type.c_str(), fDragData.Buffer, fDragData.Size);
            ImGui::EndDragDropSource();
        }
    }
    if (fDropFunction.second)
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(fDropFunction.first.c_str()))
            {
                EDragData data;
                data.Type = fDropFunction.first;
                data.Buffer = payload->Data;
                data.Size = payload->DataSize;
                fDropFunction.second(data);
            }
            ImGui::EndDragDropTarget();
        }
    }
    OnRenderEnd();

    if (GImGui->CurrentWindow->IDStack.Size > 1)
    {
        //ImGui::PopID();
    }
}

bool EUIField::OnRender() 
{
    return true;
}

void EUIField::OnRenderEnd() 
{
    if (ImGui::IsItemClicked()) 
    { 
        fEventDispatcher.Enqueue<EUIClickEvent>(EUIClickEvent());
    }
}

void EUIField::SetUpdateFunction(UpdateFunction function) 
{
    fCustomUpdateFunction = function;   
}

ERef<EUIField> EUIField::AddChild(const ERef<EUIField>& child) 
{
    if (!child) { return nullptr; }
    fChildren.push_back(child);
    return fChildren.back();
}

void EUIField::ClearChildren()
{
    fChildren.clear();
}

void EUIField::SetVisible(bool visible) 
{
    fVisible = visible;
}

void EUIField::SetDirty(bool value) 
{
    fIsDirty = value;
    for (ERef<EUIField> child : fChildren)
    {
        child->SetDirty(value);
    }
}

bool EUIField::IsDirty() const
{
    if (fIsDirty) { return true; }
    for (ERef<EUIField> child : fChildren)
    {
        if (child->IsDirty()) { return true; }
    }
    return false;
}

void EUIField::SetDragData(EDragData data) 
{
    fDragData = {};
    fDragData.Type = data.Type;
    fDragData.Size = data.Size;
    fDragData.Buffer = malloc(data.Size);
    memcpy(fDragData.Buffer, data.Buffer, data.Size);    
}

void EUIField::OnDrop(const EString& type, DropFunction dropFunction) 
{
    fDropFunction = {type, dropFunction};
}

EEventDispatcher& EUIField::GetEventDispatcher() 
{
    return fEventDispatcher;
}

// --------------------------------
// UI Label

EUILabel::EUILabel(const EString& label) 
    : EUIField(label)
{

}


bool EUILabel::OnRender() 
{
    ImGui::Text("%s", fLabel.c_str());
    return true;
}

// --------------------------------
// UI Container just to manage children
EUIContainer::EUIContainer(const EString& identifier) 
    : EUIField(identifier), fShow(false)
{
    
}

bool EUIContainer::OnRender() 
{
    if (fShow)
    {
        return ImGui::CollapsingHeader(GetDisplayName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);
    }
    return true;
}

void EUIContainer::SetShow(bool value) 
{
    fShow = value;
}


// ----------------------------------------------------------------------------------------------------
// UI Panel

EUIPanel::EUIPanel(const EString& panelName) 
    : EUIField(panelName), fOpen(true), fWasJustClosed(false)
{
    
}

const EString& EUIPanel::GetPanelTitle() const
{
    return fLabel;
}


bool EUIPanel::OnRender() 
{
    EUIField::OnRender();
    if (fOpen)
    {
        ImGui::Begin(GetDisplayName().c_str(), &fOpen);
        if (!fOpen) { fWasJustClosed = true; }
    }
    return fOpen;
}

void EUIPanel::OnRenderEnd() 
{
    EUIField::OnRenderEnd();
    if (fOpen || fWasJustClosed)
    {
        fWasJustClosed = false;
        ImGui::End();
    }
}

void EUIPanel::Open() 
{
    fOpen = true;
}

bool EUIPanel::IsOpen() const
{
    return fOpen;
}



// ----------------------------------------------------------------------------------------------------
// UI Input Field String
EUIInputFieldString::EUIInputFieldString(const EString& label) 
    : EUIField(label)
{
    memset(fValue, 0, STRING_BUFFER_SIZE);
}

bool EUIInputFieldString::OnRender() 
{
    if (ImGui::InputText(GetDisplayName().c_str(), fValue, STRING_BUFFER_SIZE))
    {
        fEventDispatcher.Enqueue<EStringChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldString::SetValue(const EString& value) 
{
    if (value.length() > STRING_BUFFER_SIZE) { std::cout << "String is to big to be displayed in input field string" << std::endl; return; }
    strcpy(fValue, value.c_str());
}

EString EUIInputFieldString::GetValue() const
{
    return EString(fValue);
}

// --------------------------------------------------------------------
// Integer Input Field
EUIInputFieldInteger::EUIInputFieldInteger(const EString& label) 
    : EUIField(label), fValue(0)
{
    
}

bool EUIInputFieldInteger::OnRender() 
{
    if (ImGui::InputInt(GetDisplayName().c_str(), &fValue, 1, 100))
    {
        fEventDispatcher.Enqueue<EIntegerChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldInteger::SetValue(i32 value) 
{
    fValue = value;
}

i32 EUIInputFieldInteger::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Float Input Field
EUIInputFieldFloat::EUIInputFieldFloat(const EString& label) 
    : EUIField(label), fValue(0)
{
    
}

bool EUIInputFieldFloat::OnRender() 
{
    if (ImGui::InputFloat(GetDisplayName().c_str(), &fValue, 0.0f, 0.0f, "%.3f"))
    {
        fEventDispatcher.Enqueue<EFloatChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat::SetValue(float value) 
{
    fValue = value;
}

float EUIInputFieldFloat::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Float Input2 Field
EUIInputFieldFloat2::EUIInputFieldFloat2(const EString& label) 
    : EUIField(label), fValue(0.0f)
{
    
}

bool EUIInputFieldFloat2::OnRender() 
{
    if (ImGui::DragFloat2(GetDisplayName().c_str(), &fValue.x))
    {
        fEventDispatcher.Enqueue<EFloat2ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat2::SetValue(const EVec2& value) 
{
    fValue = value;
}

EVec2 EUIInputFieldFloat2::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Input Field Float3
EUIInputFieldFloat3::EUIInputFieldFloat3(const EString& label) 
    : EUIField(label), fValue(0.0f)
{
    
}


bool EUIInputFieldFloat3::OnRender() 
{
    if (ImGui::DragFloat3(GetDisplayName().c_str(), &fValue.x))
    {
        fEventDispatcher.Enqueue<EFloat3ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat3::SetValue(const EVec3& value) 
{
    fValue = value;
}

EVec3 EUIInputFieldFloat3::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Input Field Float4
EUIInputFieldFloat4::EUIInputFieldFloat4(const EString& label) 
    : EUIField(label), fValue(0.0f)
{
    
}

bool EUIInputFieldFloat4::OnRender() 
{
    if (ImGui::DragFloat4(GetDisplayName().c_str(), &fValue.x))
    {
        fEventDispatcher.Enqueue<EFloat4ChangeEvent>({GetValue()});
    }
    return true;
}

void EUIInputFieldFloat4::SetValue(const EVec4& value) 
{
    fValue = value;
}

EVec4 EUIInputFieldFloat4::GetValue() const
{
    return fValue;
}

// --------------------------------------------------------------------
// Checkbox
EUICheckbox::EUICheckbox(const EString& label) 
    : EUIField(label), fValue(false)
{
    
}

bool EUICheckbox::OnRender() 
{
    if (ImGui::Checkbox(GetDisplayName().c_str(), &fValue))
    {
        fEventDispatcher.Enqueue<ECheckboxChangeEvent>({GetValue()});
    }
    return true;
}

void EUICheckbox::SetValue(bool value) 
{
    fValue = value;
}

bool EUICheckbox::GetValue() const
{
    return fValue;
}


// ----------------------------------------
// Main Menu Bar
EUIMainMenuBar::EUIMainMenuBar() 
    : EUIField("MainMenuBar")
{

}

bool EUIMainMenuBar::OnRender() 
{
    return fOpen = ImGui::BeginMainMenuBar();
}

void EUIMainMenuBar::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndMainMenuBar();
    }
}


// ----------------------------------------
// Menu
EUIMenu::EUIMenu(const EString& displayName) 
    : EUIField(displayName), fOpen(false)
{
    
}

bool EUIMenu::OnRender() 
{
    return fOpen = ImGui::BeginMenu(GetDisplayName().c_str());
}

void EUIMenu::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndMenu();
    }
    
}


// ----------------------------------------
// Context Menu
EUIContextMenu::EUIContextMenu(const EString& displayName) 
    : EUIField(displayName), fOpen(false)
{
    
}

bool EUIContextMenu::OnRender() 
{
    return fOpen = ImGui::BeginPopupContextWindow();
}

void EUIContextMenu::OnRenderEnd() 
{
    if (fOpen)
    {
        ImGui::EndPopup();
    }
}

// ----------------------------------------
// Menu Item
EUIMenuItem::EUIMenuItem(const EString& label) 
    : EUIField(label)
{
    
}

bool EUIMenuItem::OnRender() 
{
    ImGui::MenuItem(GetDisplayName().c_str());
    return true;
}

// ----------------------------------------
// Seperator
EUISeperator::EUISeperator()
    : EUIField("Serperator")
{
    
}

bool EUISeperator::OnRender() 
{   
    ImGui::Separator();
    return true;
}

// ----------------------------------------
// Selectable
EUISelectable::EUISelectable(const EString& label) 
    : EUIField(label)
{
    
}

bool EUISelectable::OnRender() 
{
    ImGui::Selectable(GetDisplayName().c_str());
    return true;
}

// --------------------------------------------------------------------
// Viewport

EUIViewport::EUIViewport() 
    : EUIField("Viewport")
{
    fViewportWidth = 200;
    fViewportHeight = 200;
    fFrameBuffer = EFrameBuffer::Create(200, 200, EFramebufferFormat::RGBA8);
}

void EUIViewport::SetRenderFunc(RenderFunction function) 
{
    fRenderFunction = function;
}

bool EUIViewport::OnRender() 
{
    auto viewportSize = ImGui::GetContentRegionAvail();
    fViewportWidth = (u32) viewportSize.x;
    fViewportHeight = (u32) viewportSize.y;
    if (fFrameBuffer)
    {
        fFrameBuffer->Resize(fViewportWidth, fViewportHeight);
        fFrameBuffer->Bind();
        ERenderContext::s_Instance->SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});
        ERenderContext::s_Instance->Clear();
        if (fRenderFunction)
        {
            fRenderFunction(fViewportWidth, fViewportHeight);
        }
        ImGui::Image((void*)(u64)fFrameBuffer->GetColorAttachment(), viewportSize);
        fFrameBuffer->Unbind();
    }
    return true;
}

// --------------------------------------------------------------------
// Mesh Input
EUIMeshInput::EUIMeshInput() 
    : EUIField("MeshInput")
{
    this->OnDrop("_RESOURCEDRAG", [this](EDragData data){
        EString str = (char*) data.Buffer;
        ERef<EMesh> mesh = EApplication::gApp().GetActiveScene()->GetResourceManager().GetResource<EMesh>(str);
        if (mesh)
        {
            SetMesh(mesh);
        }
    });
}

void EUIMeshInput::SetMesh(ERef<EMesh> mesh) 
{
    fMesh = mesh;
    fEventDispatcher.Enqueue<EMeshChangeEvent>({mesh});
}

bool EUIMeshInput::OnRender() 
{
    static ImVec2 size = { 200, 200 };
    ImGui::Button("##mynameisjeff", size);
    if (fMesh)
    {
        ImGui::Text("%s", fMesh->GetName().c_str());
    }
    return true;
}

// --------------------------------------------------------------------
// Texture Input
EUITextureInput::EUITextureInput() 
    : EUIField("TextureInput")
{
    this->OnDrop("_RESOURCEDRAG", [this](EDragData data){
        EString str = (char*) data.Buffer;
        ERef<ETexture2D> tex = EApplication::gApp().GetActiveScene()->GetResourceManager().GetResource<ETexture2D>(str);
        if (tex)
        {
            SetTexture(tex);
        }
    });
}

void EUITextureInput::SetTexture(ERef<ETexture2D> texture) 
{
    fTexture = texture;
    fEventDispatcher.Enqueue<ETextureChangeEvent>({texture});
}

bool EUITextureInput::OnRender() 
{
    static ImVec2 size = { 200, 200 };
    ImGui::Button("##mynameisjeff", size);
    if (fTexture)
    {
        ImGui::Text("%s", fTexture->GetName().c_str());
    }
    return true;
}
