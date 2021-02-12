#pragma once

namespace Engine {

    class EApplication
    {
    private:
        GLFWwindow*                 fMainWindow;
        EObjectProperty<EScene>     fActiveScene;
        bool                        fRunning;
        double                      fFrameTime;

        EExtensionManager*          fExtensionManager;
        EResourceManager*           fResourceManager;
        EUIManager*                 fUIManager;

        EUIRenderer*                fUIRenderer;

        EEventDispatcher            fEventDispatcher;
        // TEMP
        EUIMainMenuBar      fMainMenuBar;
        ERef<ECamera>     fCamera;
    public:
        EApplication();
        ~EApplication();

        void Start(const ERef<EScene>& scene = nullptr);

        void Update(float delta);
        void Render();
        void RenderImGui();
        void CleanUp();
        
        double                      GetFrameTime() const;
        EResourceManager&           GetResourceManager();
        EUIManager&                 GetUIManager();
        EUIMainMenuBar&               GetMainMenuBar();
        ERef<EUIPanel>              GetPanelByName(const EString& name);
        EObjectProperty<EScene>&    GetActiveScene();

        ImGuiContext*       GetMainImGuiContext() const;

        template <typename T, typename... Args>
        void QueueEvent(Args &&... args)
        {
            fEventDispatcher.Enqueue<T>(std::forward<Args>(args)...);
        }
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