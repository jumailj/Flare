#include "EditorLayer.h"

#include <imgui.h>
#include <ImGuizmo.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Flare/Scene/SceneSerializer.h>
#include <Flare/Utils/PlatformUtils.h>
#include <Flare/Math/Math.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>


namespace Flare{


EditorLayer::EditorLayer()
    :Layer("EditorLayer"), m_CameraController(1280.0f/720.0f, true)
{
  
}

void EditorLayer::OnAttach() 
{

	//framebuffer;
	Flare::FramebufferSpecification fbSpec;
	fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_FrameBuffer = Flare::Framebuffer::Create(fbSpec);


	m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");

	m_ActiveScene = CreateRef<Scene>(); // createa a scene;

	// auto commandLineArgs = Application::Get().GetCommandLineArgs();
	// 	if (commandLineArgs.Count > 1)
	// 	{
	// 		auto sceneFilePath = commandLineArgs[1];
	// 		SceneSerializer serializer(m_ActiveScene);
	// 		serializer.Deserialize(sceneFilePath);
	// 	}


	m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);


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
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			// set vieport size;
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}


		//update
		if(m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
			m_EditorCamera.OnUpdate(ts);
		}


		//Render 
		Flare::Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();

		//clear our entity id attachment to -1
		m_FrameBuffer->ClearAttachment(1,-1);
		

		//update scene
		// m_ActiveScene->OnUpdateRuntime(ts);  // ECS
		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

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

		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && m_GizmoType == -1) // should be !=
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

		ImGui::End();
			
	}


	void EditorLayer::OnEvent(Flare::Event& event) 
	{
		// m_CameraController.OnEvent(event);
		m_EditorCamera.OnEvent(event);

		
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
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::E:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::R:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
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
