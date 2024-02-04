

#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <Core/Application.h>

//temporary;

 #include "GLFW/glfw3.h"
// #include <glad/glad.h>
#define GL_SILENCE_DEPRECATION

namespace Flare 
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// LOG_INFO(" 1.GuiLayer_Onattach");

		// // Setup Dear ImGui context
		// IMGUI_CHECKVERSION();
		// ImGui::CreateContext();
		// ImGuiIO& io = ImGui::GetIO(); (void)io;
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		// //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		// //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		// //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// // Setup Dear ImGui style
		// ImGui::StyleColorsDark();
		// //ImGui::StyleColorsClassic();

		// // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		// ImGuiStyle& style = ImGui::GetStyle();
		// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		// {
		// 	style.WindowRounding = 0.0f;
		// 	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		// }

		// Application& app = Application::Get();
		// GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// // Setup Platform/Renderer bindings
		// ImGui_ImplGlfw_InitForOpenGL(window, true);
		// ImGui_ImplOpenGL3_Init("#version 410");


				ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 330"); // dont' sure about it, default working version, need to change to 330

	}

	void ImGuiLayer::OnUpdate()
	{
		LOG_INFO("ONUPDATE");
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}




	void ImGuiLayer::OnDetach()
	{
	   	// LOG_INFO("2. GuiLayer_OnDetach");

		// ImGui_ImplOpenGL3_Shutdown();
		// ImGui_ImplGlfw_Shutdown();
		// ImGui::DestroyContext();
	}

	// working greate;
	void ImGuiLayer::OnEvent(Event& e) // run in loop
	{
	   // 	LOG_INFO("GuiLayer_Events");
		// if (m_BlockEvents)
		// {
		// 	ImGuiIO& io = ImGui::GetIO();
		// 	e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		// 	e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		// }

       // LOG_INFO("im gui on event: {0}", e.ToString());
	}

	// working greate;
	void ImGuiLayer::Begin()
	{
		 // LOG_INFO("3. GuiLayer_Begin");

    //   //   LOG_TRACE("im gui Begin");
	// 	ImGui_ImplOpenGL3_NewFrame();
	// 	ImGui_ImplGlfw_NewFrame();
	// 	ImGui::NewFrame();
	}

	//working greate;
	void ImGuiLayer::End()
	{
		//  LOG_INFO("4. GuiLayer_End");
		// ImGuiIO& io = ImGui::GetIO();
		// Application& app = Application::Get();
		// io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// // Rendering
		// ImGui::Render();
		// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		// {
		// 	GLFWwindow* backup_current_context = glfwGetCurrentContext();
		// 	ImGui::UpdatePlatformWindows();
		// 	ImGui::RenderPlatformWindowsDefault();
		// 	glfwMakeContextCurrent(backup_current_context);
		// }
	}

	// working great;
	void ImGuiLayer::OnImGuiRender() // run in loop
	{
		// LOG_INFO("Render");
      
		// ImGui::Begin("Settings");
		// ImGui::Text("Renderer2D Stats:");
		// ImGui::End();

	}

}