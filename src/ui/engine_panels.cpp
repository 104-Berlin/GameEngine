#include "Engine.h"

using namespace Engine;


EPanelComponentData::~EPanelComponentData() 
{
    ClearComponentData();    
}

void EPanelComponentData::AddComponentDescription(ComponentDescription* dsc) 
{
    EPanelComponentData::sComponentDescriptions.push_back(dsc);   
}

const EVector<ComponentDescription*>& EPanelComponentData::GetComponentDescription() 
{
    return sComponentDescriptions;
}

void EPanelComponentData::ClearComponentData() 
{
    for (ComponentDescription* data : sComponentDescriptions)
    {
        delete data;
    }
    sComponentDescriptions.clear();
}

EPanelComponentData& EPanelComponentData::data() 
{
    static EPanelComponentData data;
    return data;
}
namespace Engine {
namespace ApplicationPanels {
    void CreateDefaultApplicationPanels() 
    {
        // ---------------------------------------------------------------------------------
        ERef<EUIPanel> componentsPanel = EMakeRef(EUIPanel, PANEL_NAME_COMPONENT);
        ERef<EUIField> panelsContainer = componentsPanel->AddChild(EMakeRef(EUIContainer, "Components Container"));
        panelsContainer->SetUpdateFunction([](ERef<EUIField> panel){
            panel->ClearChildren();
            EObject object = EApplication::gApp().GetActiveScene()->GetSelectedObject().GetValue();
            if (!object) { return; }
            for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
            {
                if (compDsc->Has(object))
                {
                    panel->AddChild(compDsc->CreateUIField(object));
                }
            }}
        );

        ERef<EUIField> componentsContextMenu = componentsPanel->AddChild(EMakeRef(EUIContextMenu));
        for (ComponentDescription* compDsc : EPanelComponentData::data().GetComponentDescription())
        {
            ERef<EUIMenuItem> menuItem = EMakeRef(EUIMenuItem, compDsc->Name);
            
            menuItem->SetOnClick([compDsc](){
                EObject object = EApplication::gApp().GetActiveScene()->GetSelectedObject().GetValue();
                if (object)
                {
                    compDsc->Create(object);
                    ERef<EUIPanel> componentPanel = EApplication::gApp().GetPanelByName(PANEL_NAME_COMPONENT);
                    if (componentPanel)
                    {
                        componentPanel->SetDirty();
                    }
                }
            });
            componentsContextMenu->AddChild(menuItem);
        }

        EApplication::gApp().GetUIManager().RegisterPanel(componentsPanel);

        // ---------------------------------------------------------------------------------
        // Scene Tree
        ERef<EUIPanel> sceneViewPanel = EMakeRef(EUIPanel, PANEL_NAME_SCENETREE);
        ERef<EUIField> objectContainer = sceneViewPanel->AddChild(EMakeRef(EUIContainer, "ObjectContainer"));
        objectContainer->SetUpdateFunction([](ERef<EUIField> sceneList){
            sceneList->ClearChildren();
            EApplication::gApp().GetActiveScene()->ForEachObject([sceneList](EObject object){
                if (object.HasComponent<ETagComponent>())
                {
                    ETagComponent& nameComponent = object.GetComponent<ETagComponent>();
                    nameComponent.Name.AddEventAfterChange((intptr_t)object.GetHandle(), [sceneList](){
                        sceneList->SetDirty();
                    });

                    ERef<EUISelectable> selectable = EMakeRef(EUISelectable, nameComponent.Name);
                    selectable->GetEventDispatcher().Connect<EUIClickEvent>([object](EUIClickEvent){
                        EApplication::gApp().GetActiveScene()->GetSelectedObject().SetValue(object);
                    });
                    sceneList->AddChild(selectable);
                }
            });
        });

        EApplication::gApp().GetActiveScene()->GetSelectedObject().AddEventAfterChange(0, [](){
            ERef<EUIPanel> panelComp = EApplication::gApp().GetPanelByName(PANEL_NAME_COMPONENT);
            ERef<EUIPanel> panelScen = EApplication::gApp().GetPanelByName(PANEL_NAME_SCENETREE);
            if (panelScen)
            {
                panelScen->SetDirty();
            }
            if (panelComp)
            {
                panelComp->SetDirty();
            }
        });

        EApplication::gApp().GetActiveScene().AddEventAfterChange((intptr_t)0, [](){
            ERef<EUIPanel> componentPanel = EApplication::gApp().GetPanelByName(PANEL_NAME_COMPONENT);
            ERef<EUIPanel> sceneTreePanel = EApplication::gApp().GetPanelByName(PANEL_NAME_SCENETREE);
            if (componentPanel) { componentPanel->SetDirty(); }
            if (sceneTreePanel) { sceneTreePanel->SetDirty(); }

            EApplication::gApp().GetActiveScene()->GetSelectedObject().AddEventAfterChange(0, [](){
                ERef<EUIPanel> panelComp = EApplication::gApp().GetPanelByName(PANEL_NAME_COMPONENT);
                ERef<EUIPanel> panelScen = EApplication::gApp().GetPanelByName(PANEL_NAME_SCENETREE);
                if (panelScen)
                {
                    panelScen->SetDirty();
                }
                if (panelComp)
                {
                    panelComp->SetDirty();
                }
            });
        });

        // Context Menu
        ERef<EUIField> contextMenu = sceneViewPanel->AddChild(EMakeRef(EUIContextMenu));
        ERef<EUIMenuItem> addObjectItem = EMakeRef(EUIMenuItem, "Add Object");
        addObjectItem->GetEventDispatcher().Connect<EUIClickEvent>([](){
            EApplication::gApp().GetActiveScene()->CreateObject();
            ERef<EUIPanel> sceneTreePanel = EApplication::gApp().GetPanelByName(PANEL_NAME_SCENETREE);
            if (sceneTreePanel) { sceneTreePanel->SetDirty(); }
        });
        contextMenu->AddChild(addObjectItem);

        EApplication::gApp().GetUIManager().RegisterPanel(sceneViewPanel);



        // ------------------------------------------------------------------------------------------------------------
        // Resource Panel

        ERef<EUIPanel> resourcePanel = EMakeRef(EUIPanel, PANEL_NAME_RESOURCES);
        resourcePanel->SetUpdateFunction([](ERef<EUIField> uiField){
            uiField->ClearChildren();
            for (auto& res : EApplication::gApp().GetResourceManager())
            {
                ERef<EUISelectable> selectable = EMakeRef(EUISelectable, res.first);
                EDragData data;
                data.Type = "_RESOURCEDRAG";
                data.Buffer = (void*)res.first.c_str();
                data.Size = res.first.length() + 1;
                selectable->SetDragData(data);
                uiField->AddChild(selectable);
            }
        });
        

        EApplication::gApp().GetResourceManager().SetOnWorkFinished([](){
            ERef<EUIPanel> resourcePanel = EApplication::gApp().GetPanelByName(PANEL_NAME_RESOURCES);
            if (resourcePanel)
            {
                resourcePanel->SetDirty();
            }
        });

        EApplication::gApp().GetUIManager().RegisterPanel(resourcePanel);


        // ------------------------------------------------------------------------------------------------------------
        // Test Viewport

        ERef<EUIPanel> viewportPanel = EMakeRef(EUIPanel, PANEL_NAME_VIEWPORT);
        ERef<EUIViewport> viewport = EMakeRef(EUIViewport);
        viewport->SetRenderFunc([](u32 width, u32 height){
            for (EEntity entity : EApplication::gApp().GetActiveScene()->view<ECameraComponent, ETransformComponent>())
            {
                EObject object(entity, EApplication::gApp().GetActiveScene().GetValue().get());
                ECameraComponent& cameraComponent = object.GetComponent<ECameraComponent>();
                ETransformComponent& cameraTransformComponent = object.GetComponent<ETransformComponent>();
                if (cameraComponent.Active)
                {
                    ERenderer::Begin(cameraComponent.Camera, glm::inverse((EMat4)cameraTransformComponent), {}, width, height);
                    for (EEntity entity : EApplication::gApp().GetActiveScene()->view<EMeshComponent, ETransformComponent>())
                    {
                        EObject object(entity, EApplication::gApp().GetActiveScene().GetValue().get());
                        EMeshComponent& meshComponent = object.GetComponent<EMeshComponent>();
                        ETransformComponent& transformComponent = object.GetComponent<ETransformComponent>();
                        if (meshComponent.Mesh)
                        {
                            ERenderer::Draw(meshComponent.Mesh->fVertexArray, transformComponent);
                        }
                    }
                }

                ERenderer::End();
                break;
            }
        });
        viewportPanel->AddChild(viewport);

        EApplication::gApp().GetUIManager().RegisterPanel(viewportPanel);
    }

    void CreateDefaultMainMenuBar() 
    {
        ERef<EUIMainMenuBar> mainMenuBar = EApplication::gApp().GetMainMenuBar();
        ERef<EUIField> fileMenu = mainMenuBar->AddChild(EMakeRef(EUIMenu, "File"));
        ERef<EUIField> saveFile = fileMenu->AddChild(EMakeRef(EUIMenuItem, "Save"));
        saveFile->SetOnClick([](){
            EFileWriter::WriteScene(EApplication::gApp().GetActiveScene(), EFile("Test.esc"));
        });
        fileMenu->AddChild(EMakeRef(EUIMenuItem, "Open"))->SetOnClick([](){
            EVector<EString> results = Platform::OpenFileDialog("Test", "", {});
            for (const EString& str : results)
            {
                EFile file(str);
                if (file.Exist())
                {
                    EApplication::gApp().SetActiveScene(EFileReader::ReadScene(file));
                }
                break; // For now we can only load one scene. This will be fixed in the future
            }
        });



        ERef<EUIField> editMenu = mainMenuBar->AddChild(EMakeRef(EUIMenu, "Edit"));
        
        
        // View Menu
        ERef<EUIMenu> viewMenu = std::dynamic_pointer_cast<EUIMenu>(mainMenuBar->AddChild(EMakeRef(EUIMenu, "View")));
        for (ERef<EUIPanel> panel : EApplication::gApp().GetUIManager().GetPanels())
        {
            ERef<EUIMenuItem> menuItem = ERef<EUIMenuItem>(new EUIMenuItem(panel->GetDisplayName()));
            menuItem->GetEventDispatcher().Connect<EUIClickEvent>([panel](){
                if (panel->IsOpen())
                {
                    ImGui::SetWindowFocus(panel->GetDisplayName().c_str());
                }
                else
                {
                    panel->Open();
                }
            });
            viewMenu->AddChild(menuItem);
        }     
    }
}}
