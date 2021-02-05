#pragma once

namespace Engine {

    class EApplication
    {
    private:
        GLFWwindow*                 fMainWindow;
        EObjectProperty<EScene>     fActiveScene;
        bool                        fRunning;

        EExtensionManager*           fExtensionManager;
        EResourceManager*            fResourceManager;
        EUIManager*                  fUIManager;

        EUIRenderer*                fUIRenderer;

        // TEMP
        EMainMenuBar      fMainMenuBar;
        ERef<ECamera>     fCamera;
    public:
        EApplication();
        ~EApplication();

        void Start(const ERef<EScene>& scene = nullptr);

        void Update(float delta);
        void Render();
        void RenderImGui();
        void CleanUp();

        EResourceManager&   GetResourceManager();
        EUIManager&         GetUIManager();

        ERef<EUIPanel>      GetPanelByName(const EString& name);

        ImGuiContext* GetMainImGuiContext() const;

        ERef<EScene> GetActiveScene() const;
    private:
        void Run();

        void SetUpMainMenuBar();
        void RegisterInternComponents();
        void RegisterInternPanels();

        void CreateMainWindow();
    public:
        static EApplication& gApp();
    };




    namespace UI {
        template <typename Resource>
        static void RenderResourceField(const EString& label, EObjectProperty<Resource>* value)
        {
            ImGui::Text("%s", label.c_str());
            if (!value->GetValue())
            {
                ImGui::Button("##RESOURCEDRAGIN", ImVec2(200, 200));
            }
            else
            {
                ImGui::Selectable((*value)->GetName().c_str(), false);
            }
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_RESOURCEDRAG"))
                {
                    EString nameIdent = EString((const char*)payload->Data);
                    ERef<Resource> textureRes = EApplication::gApp().GetResourceManager().GetResource<Resource>(nameIdent);
                    if (textureRes)
                    {
                        value->SetValue(textureRes);
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }
        
        template <>
        inline void RenderInputField<EObjectProperty<ETexture2D>*>(const EString& label, EObjectProperty<ETexture2D>* value)
        {
            RenderResourceField(label, value);
        }

        template <>
        inline void RenderInputField<EObjectProperty<EMesh>*>(const EString& label, EObjectProperty<EMesh>* value)
        {
            RenderResourceField(label, value);
        }

        template <>
        inline void RenderInputField<EObjectProperty<ECamera>*>(const EString& label, EObjectProperty<ECamera>* value)
        {
        }
    }

}