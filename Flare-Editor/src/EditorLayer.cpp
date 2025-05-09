#include "EditorLayer.h"

#include <imgui.h>
#include <ImGuizmo.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Flare/Scene/SceneSerializer.h>
#include <Flare/Core/Log.h>
#include <Flare/Utils/PlatformUtils.h>
#include <Flare/Math/Math.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>


namespace Flare{

	void SetNightOwlThemeColors()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;
	
		// Background
		colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.09f, 0.15f, 1.0f); // #011627
	
		// Headers
		colors[ImGuiCol_Header] = ImVec4(0.12f, 0.20f, 0.28f, 1.0f); // Slightly lighter blue
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active header
	
		// Buttons
		colors[ImGuiCol_Button] = ImVec4(0.12f, 0.20f, 0.28f, 1.0f); // Button background
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active button
	
		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.16f, 0.24f, 1.0f); // Frame background
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.20f, 0.30f, 1.0f); // Hover effect
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.12f, 0.25f, 0.35f, 1.0f); // Active frame
	
		// Tabs
		colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.16f, 0.24f, 1.0f); // Tab background
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_TabActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active tab
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.10f, 0.15f, 1.0f); // Unfocused tab
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.08f, 0.16f, 0.24f, 1.0f); // Active unfocused tab
	
		// Title
		colors[ImGuiCol_TitleBg] = ImVec4(0.01f, 0.09f, 0.15f, 1.0f); // Title background
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.16f, 0.24f, 1.0f); // Active title
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.01f, 0.09f, 0.15f, 1.0f); // Collapsed title
	
		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01f, 0.09f, 0.15f, 1.0f); // Scrollbar background
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.12f, 0.20f, 0.28f, 1.0f); // Scrollbar grab
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active scrollbar
	
		// Checkmarks
		colors[ImGuiCol_CheckMark] = ImVec4(0.50f, 0.80f, 0.90f, 1.0f); // Teal
	
		// Slider
		colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.80f, 0.90f, 1.0f); // Teal
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.90f, 1.00f, 1.0f); // Active teal
	
		// Text
		colors[ImGuiCol_Text] = ImVec4(0.84f, 0.87f, 0.93f, 1.0f); // Light blue
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.55f, 0.60f, 1.0f); // Disabled text
	
		// Separators
		colors[ImGuiCol_Separator] = ImVec4(0.12f, 0.20f, 0.28f, 1.0f); // Separator
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active separator
	
		// Resize Grip
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.12f, 0.20f, 0.28f, 1.0f); // Resize grip
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.14f, 0.25f, 0.35f, 1.0f); // Hover effect
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.16f, 0.30f, 0.40f, 1.0f); // Active resize grip
	
		// Popups (including tooltips)
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.16f, 0.24f, 1.0f); // Popup background
	}


	void SetGruvboxThemeColors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Background
    colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // #282828

    // Headers
    colors[ImGuiCol_Header] = ImVec4(0.29f, 0.32f, 0.31f, 1.0f); // #4C4C4C
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active header

    // Buttons
    colors[ImGuiCol_Button] = ImVec4(0.29f, 0.32f, 0.31f, 1.0f); // Button background
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active button

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Frame background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f); // Hover effect
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active frame

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Tab background
    colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_TabActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active tab
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // Unfocused tab
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Active unfocused tab

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // Title background
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Active title
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // Collapsed title

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f); // Scrollbar background
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.29f, 0.32f, 0.31f, 1.0f); // Scrollbar grab
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active scrollbar

    // Checkmarks
    colors[ImGuiCol_CheckMark] = ImVec4(0.73f, 0.53f, 0.34f, 1.0f); // Yellowish

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4(0.73f, 0.53f, 0.34f, 1.0f); // Yellowish
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.83f, 0.63f, 0.44f, 1.0f); // Active yellowish

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.86f, 0.69f, 1.0f); // Light beige
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f); // Disabled text

    // Separators
    colors[ImGuiCol_Separator] = ImVec4(0.29f, 0.32f, 0.31f, 1.0f); // Separator
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active separator

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.29f, 0.32f, 0.31f, 1.0f); // Resize grip
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.35f, 0.40f, 0.38f, 1.0f); // Hover effect
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.45f, 0.50f, 0.48f, 1.0f); // Active resize grip

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Popup background
}

void SetUnrealEngineThemeColors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Background
    colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.0f); // Dark gray

    // Headers
    colors[ImGuiCol_Header] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Slightly lighter gray
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active header

    // Buttons
    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Button background
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active button

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Frame background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active frame

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Tab background
    colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active tab
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f); // Unfocused tab
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Active unfocused tab

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.0f); // Title background
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Active title
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.02f, 0.02f, 0.02f, 1.0f); // Collapsed title

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.0f); // Scrollbar background
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Scrollbar grab
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active scrollbar

    // Checkmarks
    colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f); // White

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f); // White
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.0f); // Active white

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f); // Light gray
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f); // Disabled text

    // Separators
    colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Separator
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active separator

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Resize grip
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Hover effect
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f); // Active resize grip

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Popup background

    // Style adjustments
    style.FrameRounding = 4.0f;
    style.WindowRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
}





extern const std::filesystem::path g_AssetPath;

EditorLayer::EditorLayer()
    :Layer("EditorLayer"), m_CameraController(1280.0f/720.0f, true)
{
  
}

void EditorLayer::OnAttach() 
{

	SetGruvboxThemeColors();


	//framebuffer;
	Flare::FramebufferSpecification fbSpec;
	fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_FrameBuffer = Flare::Framebuffer::Create(fbSpec);


	m_IconPlay = Flare::Texture2D::Create("Resource/icons/PlayButton.png");
	m_IconStop = Flare::Texture2D::Create("Resource/icons/StopButton.png");
	
	
	m_ActiveScene = CreateRef<Scene>(); // createa a scene;

	auto commandLineArgs = Application::Get().GetSpecification().CommandLineArgs;
		if (commandLineArgs.Count > 1)
		{
			auto sceneFilePath = commandLineArgs[1];
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(sceneFilePath);
		}


	m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
	Renderer2D::SetLineWidth(4.0f);


}

void EditorLayer::OnDetach() {

}


void EditorLayer::OnUpdate(Flare::Timestep ts) {
    // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		// Resize

		if (FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			// set vieport size;
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}


		//update
		// if(m_ViewportFocused)
		// {
		// 	m_CameraController.OnUpdate(ts);
		// 	m_EditorCamera.OnUpdate(ts);
		// }


		//Render 
		Flare::Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();

		//clear our entity id attachment to -1
		m_FrameBuffer->ClearAttachment(1,-1);
		

		//update scene
		//  m_ActiveScene->OnUpdateRuntime(ts);  // ECS
		//  m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		switch (m_SceneState)
		{
			case SceneState::Edit:
			{
				if (m_ViewportFocused)
					m_CameraController.OnUpdate(ts);

				m_EditorCamera.OnUpdate(ts);

				m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);
				break;
			}
			case SceneState::Play:
			{
				m_ActiveScene->OnUpdateRuntime(ts);
				break;
			}
		}




		auto[mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportWidth = m_ViewportBounds[1]  - m_ViewportBounds[0];
		
		//flip-y cord
		my = m_ViewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;


		if(mouseX >= 0 && mouseY >= 0 && mouseX < (int)m_ViewportSize.x && mouseY < (int) m_ViewportSize.y)
		{
			int pixeldata = m_FrameBuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixeldata == -1 ? Entity() : Entity((entt::entity)pixeldata, m_ActiveScene.get());
		}

		
		OnOverlayRender();
		

		m_FrameBuffer->Unbind();
			
}

void EditorLayer::OnImGuiRender() 
{

		ImGui::SetNextWindowBgAlpha(0.5f);

			// READ THIS !!!
			// TL;DR; this demo is more complicated than what most users you would normally use.
			// If we remove all options we are showcasing, this demo would become:
			//     void ShowExampleAppDockSpace()
			//     {
			//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			//     }
			// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
			// In this specific demo, we are not using DockSpaceOverViewport() because:
			// - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
			// - (2) we allow the host window to have padding (when opt_padding == true)
			// - (3) we expose many flags and need a way to have them visible.
			// - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
			//      in your code, but we don't here because we allow the window to be floating)

				//enable dock space;
				static bool dockspaceOpen = true;
				static bool opt_fullscreen_persistant = true;
				bool opt_fullscreen = opt_fullscreen_persistant;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
				// because it would be confusing to have two docking targets within each others.
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				if (opt_fullscreen)
				{
					const ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->WorkPos);
					ImGui::SetNextWindowSize(viewport->WorkSize);
					ImGui::SetNextWindowViewport(viewport->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}
				

				// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
				// and handle the pass-thru hole, so we ask Begin() to not render a background.
				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
				// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
				// all active windows docked into it will lose their parent and become undocked.
				// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
				// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);



				// Submit the DockSpace
				ImGuiIO& io = ImGui::GetIO();
				ImGuiStyle& style = ImGui::GetStyle();
				float minWinSizeX = style.WindowMinSize.x;
				style.WindowMinSize.x = 270.0f;

				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						// Disabling fullscreen would allow the window to be moved to the front of other windows,
						// which we can't undo at the moment without finer window depth/z control.
						// ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
						
						// new file
						if(ImGui::MenuItem("New", "Ctrl+N")){NewScene();}

						// opening file
						if(ImGui::MenuItem("Open", "Ctrl+O")){OpenScene();}

						// save file
						if(ImGui::MenuItem("save", "Ctrl+S")){SaveScene();}

						//saving file
						if(ImGui::MenuItem("Save As", "Ctrl+Shift+S")){SaveSceneAs();}

						//exit program
						if(ImGui::MenuItem("Exit"))
						{
							 Flare::Application::Get().Close();
						}
						
						ImGui::EndMenu();


					}

					ImGui::EndMenuBar();
				}

				// new imgui windows;
				m_SceneHierarchyPanel.OnImGuiRender();
				m_ContentBrowserPanel.OnImGuiRender();


				ImGui::Begin("stats");

				std::string name = "None";
				if(m_HoveredEntity){
					name =  m_HoveredEntity.GetComponent<TagComponent>().Tag;
				}
				ImGui::Text("Hovered Entity: %s",name.c_str());

				auto stats = Flare::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("indices: %d", stats.GetTotalIndexCount());

				ImGui::End();


				ImGui::Begin("Settings");
				ImGui::Checkbox("Show physics colliders", &m_ShowPhysicsColliders);
				ImGui::End();



				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));

					ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


		// file draging for content browser
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				OpenScene(std::filesystem::path(g_AssetPath) / path);
			}
			ImGui::EndDragDropTarget();
		}


		// Gizmos
		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

			// Camera
			
			// Runtime camera from entity
			// auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			// const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			// const glm::mat4& cameraProjection = camera.GetProjection();
			// glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		UI_Toolbar();

		ImGui::End();		
	}


	void EditorLayer::UI_Toolbar()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		auto& colors = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		const auto& buttonActive = colors[ImGuiCol_ButtonActive];
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

		ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		float size = ImGui::GetWindowHeight() - 4.0f;
		Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
		if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(icon->GetRendererID())), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
		{
			if (m_SceneState == SceneState::Edit)
				OnScenePlay();
			else if (m_SceneState == SceneState::Play)
				OnSceneStop();
		}
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}


	void EditorLayer::OnEvent(Flare::Event& event) 
	{
		m_CameraController.OnEvent(event);
		// m_EditorCamera.OnEvent(event);

		if (m_SceneState == SceneState::Edit)
		{
			m_EditorCamera.OnEvent(event);
		}


		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));

	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if(e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if(m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftControl))
			m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}


	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//shorcut
		if (e.IsRepeat())
			return false;
			
		//check if ctrl/shift key is pressed;
		bool controlPressed = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shiftPressed = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);


		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if(controlPressed)
					NewScene();
				
				break;
			}

			case Key::O:
			{
				if(controlPressed)
					OpenScene();
				
				break;
			}

			case Key::S:
			{
				if(controlPressed){

					if(shiftPressed){
						SaveSceneAs();
					}else{
						SaveScene();  //currently not implemented.
					}
				}
				break;
			}

			// Gizmos
			// Gizmos
			case Key::Q:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = -1;
				break;
			}
			case Key::W:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::UNIVERSAL;
				break;
			}
			case Key::E:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}
			case Key::R:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}


		}
		return false;
	}


	
	void EditorLayer::OnOverlayRender()
	{


		if (m_SceneState == SceneState::Play)
		{
			Entity camera = m_ActiveScene->GetPrimaryCameraEntity();
			Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform());
		}
		else
		{
			Renderer2D::BeginScene(m_EditorCamera);
		}

		if (m_ShowPhysicsColliders)
		{
			// Box Colliders
			{
				auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();
				for (auto entity : view)
				{
					auto [tc, bc2d] = view.get<TransformComponent, BoxCollider2DComponent>(entity);

					glm::vec3 translation = tc.Translation + glm::vec3(bc2d.Offset, 0.001f);
					glm::vec3 scale = tc.Scale * glm::vec3(bc2d.Size * 2.0f, 1.0f);

					// glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
					// 	* glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
					// 	* glm::scale(glm::mat4(1.0f), scale);

					
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
					* glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
					* glm::translate(glm::mat4(1.0f), glm::vec3(bc2d.Offset, 0.001f))
					* glm::scale(glm::mat4(1.0f), scale);

					Renderer2D::DrawRect(transform, glm::vec4(0, 1, 0, 1));
				}
			}

			// Circle Colliders
			{
				auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, CircleCollider2DComponent>();
				for (auto entity : view)
				{
					auto [tc, cc2d] = view.get<TransformComponent, CircleCollider2DComponent>(entity);

					glm::vec3 translation = tc.Translation + glm::vec3(cc2d.Offset, 0.001f);
					glm::vec3 scale = tc.Scale * glm::vec3(cc2d.Radius * 2.0f);

					glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
						* glm::scale(glm::mat4(1.0f), scale);

					Renderer2D::DrawCircle(transform, glm::vec4(0, 1, 0, 1), 0.01f);
				}
			}
		}

				// Draw selected entity outline 
				if (Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity())
				{
					const TransformComponent& transform = selectedEntity.GetComponent<TransformComponent>();
					Renderer2D::DrawRect(transform.GetTransform(), glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
		
				}

				// test area:


		Renderer2D::EndScene();
	}


	

	void EditorLayer::NewScene()
	{
		m_ActiveScene= CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		m_EditorScenePath = std::filesystem::path();  //todo, not declared

	}
	
	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Flare Scene (*.flare)\0*.flare\0");
		if (!filepath.empty())
			OpenScene(filepath);
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if(m_SceneState != SceneState::Edit)
			OnSceneStop();

		if (path.extension().string() != ".flare")
		{
			LOG_WARN("Could not load {0} - not a scene file", path.filename().string());
			return;
		}
		
		Ref<Scene> newScene = CreateRef<Scene>();
		SceneSerializer serializer(newScene);
		if (serializer.Deserialize(path.string()))
		{
			m_EditorScene = newScene;
			m_EditorScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_EditorScene);

			m_ActiveScene = m_EditorScene;
			m_EditorScenePath = path;
		}
	}

	void EditorLayer::SaveScene()
	{
		if (!m_EditorScenePath.empty())
			SerializeScene(m_ActiveScene, m_EditorScenePath);
		else
			SaveSceneAs();
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Flare Scene (*.flare)\0*.flare\0");
		if (!filepath.empty())
		{
			SerializeScene(m_ActiveScene, filepath);
			m_EditorScenePath = filepath;
		}
	}

	void EditorLayer::SerializeScene(Ref<Scene> scene, const std::filesystem::path& path)
	{
		SceneSerializer serializer(scene);
		serializer.Serialize(path.string());
	}

	void EditorLayer::OnScenePlay()
	{
		m_SceneState = SceneState::Play;

		m_ActiveScene = Scene::Copy(m_EditorScene);
		m_ActiveScene->OnRuntimeStart();

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnSceneStop()
	{
		m_SceneState = SceneState::Edit;

		m_ActiveScene->OnRuntimeStop();
		m_ActiveScene = m_EditorScene;

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDuplicateEntity()
	{
		if (m_SceneState != SceneState::Edit)
			return;

		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity)
			m_EditorScene->DuplicateEntity(selectedEntity);
	}



}
