#pragma once

#include <Flare/Core/Flare.h>

#include "Panels/SceneHierarchyPanel.h"
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

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	public:
		OrthographicCameraController m_CameraController;


		Ref<Texture2D>m_CheckTexture;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		EditorCamera m_EditorCamera; // added editor camera

		Ref<Framebuffer>m_FrameBuffer;
		glm::vec2 m_ViewportSize= {0.0f,0.0f};
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;

	};



}

