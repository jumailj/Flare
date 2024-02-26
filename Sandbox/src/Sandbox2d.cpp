#include "Sandbox2d.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


Sandbox2D::Sandbox2D()
    :Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, true)
{
  
}

void Sandbox2D::OnAttach() 
{

	//framebuffer;
	Flare::FramebufferSpecification fbSpec;
	fbSpec.Widht = 1280;
	fbSpec.Height = 720;
	
	m_FrameBuffer = Flare::Framebuffer::Create(fbSpec);



		m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");
		m_SpriteSheet = Flare::Texture2D::Create("Resource/game/sprteSheet.png");

			for (int y = 0 ; y <= 2 ; y++) {
					for (int x = 0; x <=15; x++) {

						std::string xval = std::to_string(x);
						std::string yval = std::to_string(y);

						std::string value = "x:"+xval+ "y:"+yval;
						//LOG_TRACE("value= {0}", value);
						s_TextureMap[value] = Flare::SubTexture2D::CreateFromCoords(m_SpriteSheet,{x,y+10}, {128,128}, {1,1});
				}
			}
}

void Sandbox2D::OnDetach() {

}


void Sandbox2D::OnUpdate(Flare::Timestep ts) {
    // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		m_CameraController.OnUpdate(ts);

		//Render 
		Flare::Renderer2D::ResetStats();
		{
			m_FrameBuffer->Bind();

			Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Flare::RenderCommand::Clear();
		}


		{

			Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
			rotate+=(15*ts);
			Flare::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.8, 0.8f}, 50.0f, m_SquareColor1);
			Flare::Renderer2D::DrawQuad({ 0.5f, -0.5f, 1.0f }, { 0.5f, 0.75f }, m_SquareColor1);
			Flare::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckTexture, 5.0f);
			Flare::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f },30.0f, m_SquareColor);
			Flare::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotate, m_CheckTexture, 1.0f);

			// Flare::Renderer2D::DrawRotatedQuad({0.0f, 0.0f,0.0f}, {1.0f, 2.0f}, 54.0f, m_TextureStairs);


			for (int y = 0 ; y <= 2 ; y++) {
			for (int x = 0; x <=15; x++) {

						std::string xval = std::to_string(x);
						std::string yval = std::to_string(y);

						std::string value = "x:"+xval+ "y:"+yval;
						//LOG_TRACE("value= {0}", value);
				    	Flare::Renderer2D::DrawQuad({x, y, 0.0f}, {1.0f, 1.0f},s_TextureMap[value] );

				}
			}
			Flare::Renderer2D::EndScene();

			m_FrameBuffer->Unbind();
			
		}
     
}

void Sandbox2D::OnImGuiRender() 
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

			static bool dockingEnabled = true;

			if (dockingEnabled)
			{
				//enable dock space;
				static bool dockspaceOpen = true;
				static bool opt_fullscreen = true;
				static bool opt_padding = false;
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
				else
				{
					dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
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
				if (!opt_padding)
					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
				if (!opt_padding)
					ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				// Submit the DockSpace
				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Options"))
					{
						// Disabling fullscreen would allow the window to be moved to the front of other windows,
						// which we can't undo at the moment without finer window depth/z control.
						// ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
						
						if(ImGui::MenuItem("Exit")) Flare::Application::Get().Close();

						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				// new imgui windows;

				ImGui::Begin("Settings");

				auto stats = Flare::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("indices: %d", stats.GetTotalIndexCount());


				// renderimage.
				uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
				ImGui::Image(reinterpret_cast<void*>(static_cast<uintptr_t>(textureID)), ImVec2{1280.0f, 720.0f});		
				ImGui::End();


				ImGui::End();
			}
}


void Sandbox2D::OnEvent(Flare::Event& event) {
     m_CameraController.OnEvent(event);
}

