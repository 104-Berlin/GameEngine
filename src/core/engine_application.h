#pragma once

namespace Engine {

    class EApplication
    {
    private:
        GLFWwindow*      fMainWindow;
        ERef<EScene>     fActiveScene;
        bool             fRunning;

        EExtensionManager   fExtensionManager;
        EResourceManager    fResourceManager;

        EUIRenderer         fUIRenderer;

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

        EResourceManager& GetResourceManager();


        ImGuiContext* GetMainImGuiContext() const;

        const ERef<EScene>& GetActiveScene() const;
    private:
        void Run();

        void SetUpMainMenuBar();
        void RegisterInternComponents();

        void CreateMainWindow();

        static void RenderResourcePanel(EResourceManager& resourceManager);
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