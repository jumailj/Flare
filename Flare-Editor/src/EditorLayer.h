#pragma once

#include <Flare/Core/Flare.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include <Flare/Renderer/EditorCamera.h>

namespace Flare{

	class EditorLayer : public Layer{

		public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();
		void OnDuplicateEntity();

		//UI Panels
		void UI_Toolbar();

	public:
		OrthographicCameraController m_CameraController;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;

		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;

		EditorCamera m_EditorCamera; // added editor camera

		Ref<Framebuffer>m_FrameBuffer;
		glm::vec2 m_ViewportSize= {0.0f,0.0f};
		glm::vec2 m_ViewportBounds[2];

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		Ref<Texture2D> m_IconPlay,m_IconStop;
		

		enum class SceneState
		{
			Edit =0, Play = 1
		};

		SceneState m_SceneState = SceneState::Edit;
	};



}

