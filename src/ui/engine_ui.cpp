#include "Engine.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

using namespace Engine;

#include <imgui_internal.h>

bool UI::IsItemActiveLastFrame() 
{
    ImGuiContext& g = *GImGui;
    if (g.ActiveIdPreviousFrame)
        return g.ActiveIdPreviousFrame == g.CurrentWindow->DC.LastItemId;
    return false;
}


void UI::Init(EWindow& window)
{
    GLFWwindow* win = window.GetNativeWindow();
    
    IN_RENDER1(win, {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        io.FontDefault = io.Fonts->AddFontFromFileTTF("OpenSans-SemiBold.ttf", 18.0f);


        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(win, true);
        ImGui_ImplOpenGL3_Init();
    })
}

void UI::NewFrame()
{
    IN_RENDER({
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        static bool p_open;

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();


		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

    })
    
}

void UI::Render()
{

    IN_RENDER({

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    })
}






void UI::RenderInputField(const EString& label, EProperty<bool>& value) 
{
    bool val = value.GetValue();
    if (ImGui::Checkbox(label.c_str(), &val))
    {
        value.SetValue(val);
    }
}

void UI::RenderInputField(const EString& label, EProperty<float>& value) 
{
    float val = value.GetValue();
    if (ImGui::DragFloat(label.c_str(), &val))
    {
        value.SetValue(val);
    }
}

void UI::RenderInputField(const EString& label, EProperty<double>& value) 
{
    double val = value.GetValue();
    if (ImGui::InputDouble(label.c_str(), &val, 0.0f, 0.0f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
    {   
        value.SetValue(val);
        std::cout << "Doulbe changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, EProperty<i32>& value) 
{
    i32 val = value.GetValue();
    if (ImGui::DragInt(label.c_str(), &val))
    {
        value.SetValue(val);
    }
}

void UI::RenderInputField(const EString& label, EProperty<EVec3>& value) 
{
    EVec3 val = value.GetValue();
    if (ImGui::DragFloat3(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
    {
        value.SetValue(val);
    }
}

void UI::RenderInputField(const EString& label, EProperty<EVec4>& value) 
{
    EVec4 val = value.GetValue();
    if (ImGui::DragFloat4(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
    {
        value.SetValue(val);
    }
}

void UI::RenderInputField(const EString& label, EProperty<EString>& value) 
{
    size_t bufferSize = 256 * sizeof(char);
    char* buffer = (char*) malloc(bufferSize);
    memset(buffer, 0, bufferSize);
    strcpy(buffer, value.GetValue().c_str());
    if (ImGui::InputText(label.c_str(), buffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        value.SetValue(buffer);
        std::cout << "String changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, EProperty<EUUID>& value) 
{
    ImGui::Text("%s", label.c_str());
    ImGui::SameLine();
    ImGui::Text("%s", value.GetValue().ToString().c_str());
}

void UI::RenderInputField(const EString& label, EObjectProperty<ETexture2D>& value) 
{
    ImGui::Text("%s", label.c_str());
    if (!value.GetValue())
    {
        ImGui::Button("##RESOURCEDRAGIN", ImVec2(200, 200));
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_RESOURCEDRAG"))
            {
                EString nameIdent = EString((const char*)payload->Data);
                ERef<ETexture2D> textureRes = EApplication::gApp().GetResourceManager().GetResource<ETexture2D>(nameIdent);
                if (textureRes)
                {
                    std::cout << "Drag texture finished" << textureRes->GetWidth() << " | " << textureRes->GetHeight() << std::endl;
                    value.SetValue(textureRes);
                }
            }
            ImGui::EndDragDropTarget();
        }
    }
    else
    {
        ImGui::Selectable(value.GetValue()->GetName().c_str(), false);
    }
    
}




void UI::RenderComponentPanel(EObject object)
{
    ImGui::Begin("Components##COMPONENTPANEL");

    if (object)
    {
        if (object.HasComponent<ETransformComponent>())
        {
            ETransformComponent& tc = object.GetComponent<ETransformComponent>();
            RenderInputField<ETransformComponent>("Transform Component", &tc);
        }
        if (object.HasComponent<TestComponent>())
        {
            TestComponent& tc = object.GetComponent<TestComponent>();
            RenderInputField("Test Component", &tc);
        }
    }
    ImGui::End();
}

void UI::RenderResourcePanel(EResourceManager& resourceManager)
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Resource Manager##RESOURCEMANAGER");
    for (auto& res : resourceManager)
    {
        ImGui::Selectable(res.first.c_str(), false);
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("_RESOURCEDRAG", res.first.c_str(), strlen(res.first.c_str()));

            EString resourceType = EResourceManager::GetResourceTypeFromFile(res.first);
            if (resourceType == typeid(ETexture2D).name())
            {
                ERef<ETexture2D> texture = std::static_pointer_cast<ETexture2D>(res.second);
                // This should not be here
                //glBindTexture(GL_TEXTURE_2D, );
                ImGui::Image((void*)(u64)texture->GetRendererID(), ImVec2(100, 100));
            }
            
            ImGui::EndDragDropSource();
        }
    }
    ImGui::End();
}
