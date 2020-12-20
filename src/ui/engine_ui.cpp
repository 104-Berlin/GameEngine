#include "Engine.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

using namespace Engine;

#include <imgui_internal.h>

bool IsItemActiveLastFrame()
{
    ImGuiContext& g = *GImGui;
    if (g.ActiveIdPreviousFrame)
        return g.ActiveIdPreviousFrame == g.CurrentWindow->DC.LastItemId;
    return false;
}

bool IsItemJustReleased()
{
    return IsItemActiveLastFrame() && !ImGui::IsItemActive();
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

void UI::RenderInputField(const EString& label, bool* value) 
{
    if (!value) { return; }
    if (ImGui::Checkbox(label.c_str(), value))
    {
        std::cout << "Changed checkbox" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, float* value) 
{
    if (!value) { return; }
    ImGui::DragFloat(label.c_str(), value);
    if (IsItemJustReleased())
    {
        std::cout << "Float Changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, double* value) 
{
    if (!value) { return; }
    if (ImGui::InputDouble(label.c_str(), value, 0.0f, 0.0f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
    {   
        std::cout << "Double changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, i32* value) 
{
    if (!value) { return; }
    ImGui::DragInt(label.c_str(), value);
    if (IsItemJustReleased())
    {
        std::cout << "Integer changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, EVec3* value) 
{
    if (!value) { return; }
    ImGui::DragFloat3(label.c_str(), &value->x);
    if (IsItemJustReleased())
    {
        std::cout << "Vector 3 changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, EVec4* value) 
{
    if (!value) { return; }
    ImGui::DragFloat4(label.c_str(), &value->x);
    if (IsItemJustReleased())
    {
        std::cout << "Vector 4 changed" << std::endl;
    }
}

void UI::RenderInputField(const EString& label, EString* value) 
{
    if (!value) { return; }

    size_t bufferSize = (value->length() + 10) * sizeof(char);
    char* buffer = (char*) malloc(bufferSize);
    strcpy(buffer, value->c_str());
    if (ImGui::InputText(label.c_str(), buffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        std::cout << "String changed" << std::endl;
    }
}
