#include "EditorLayer.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Flare/Scene/SceneSerializer.h>

#include <Flare/Utils/PlatformUtils.h>

namespace Flare{


EditorLayer::EditorLayer()
    :Layer("EditorLayer"), m_CameraController(1280.0f/720.0f, true)
{
  
}

void EditorLayer::OnAttach() 
{

	//framebuffer;
	Flare::FramebufferSpecification fbSpec;
	fbSpec.Widht = 1280;
	fbSpec.Height = 720;
	
	m_FrameBuffer = Flare::Framebuffer::Create(fbSpec);

	m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");
	// m_SpriteSheet = Flare::Texture2D::Create("Resource/game/sprteSheet.png");

	m_ActiveScene = CreateRef<Scene>(); // createa a scene;


#if 0
	//entity;
	auto square = m_ActiveScene->CreateEntity("green square"); // create new entity.
	square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });  // add sprite rendere to entity.
	m_SquareEntity = square;

	auto redsquare = m_ActiveScene->CreateEntity("red square"); // create new entity.
	redsquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });  // add sprite rendere to entity.



	m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
	m_CameraEntity.AddComponent<CameraComponent>();

	m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
	auto cc = m_SecondCamera.AddComponent<CameraComponent>();
	cc.Primary = false;

	// native scripting...

class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				 translation.x = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

#endif

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

}

void EditorLayer::OnDetach() {

}


void EditorLayer::OnUpdate(Flare::Timestep ts) {
    // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		// Resize

		if (FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Widht != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			// m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}



		if(m_ViewportFocused){m_CameraController.OnUpdate(ts);}
		

		//Render 
		Flare::Renderer2D::ResetStats();
		
		m_FrameBuffer->Bind();

		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();
		


		// Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());

		// Flare::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckTexture, 5.0f);
		// Flare::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {10,10}, {1.0f, 1.0f, 1.0f, 1.0f});
		//update scene;
		
		m_ActiveScene->OnUpdate(ts);  // ECS


		//Flare::Renderer2D::EndScene();

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


				ImGui::Begin("stats");

				auto stats = Flare::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("indices: %d", stats.GetTotalIndexCount());

				ImGui::End();


				


				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
					ImGui::Begin("Viewport");

					m_ViewportFocused = ImGui::IsWindowFocused();
					m_ViewportHovered = ImGui::IsWindowHovered();
					Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

					ImVec2 viewportPannelSize = ImGui::GetContentRegionAvail();
					m_ViewportSize = { viewportPannelSize.x, viewportPannelSize.y };
						
						// renderimage.
						uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
						ImGui::Image(reinterpret_cast<void*>(static_cast<uintptr_t>(textureID)), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0,1}, ImVec2{1,0});		
					ImGui::End();
				ImGui::PopStyleVar();

				ImGui::End();
			
}


	void EditorLayer::OnEvent(Flare::Event& event) 
	{
		// m_CameraController.OnEvent(event);

		
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(EditorLayer::OnKeyPressed));


	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		LOG_INFO("keypresseed event {0}", e.ToString());

		//shortcuts
		if(e.GetRepeatCount() >0)
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
				if(controlPressed && shiftPressed)
					SaveSceneAs();
				
				break;
			}
		}



		return false;
	}



	void EditorLayer::NewScene()
	{
		m_ActiveScene= CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);


	}
	
	void EditorLayer::OpenScene()
	{

		std::string filepath = FileDialogs::OpenFile("fix later"); // return the file path.
		if(!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
		}

	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("fix later");
		if(!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}


}
