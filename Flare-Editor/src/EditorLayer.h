#pragma once

#include <Flare/Core/Flare.h>

#include "Panels/SceneHierarchyPanel.h"

namespace Flare{

	class EditorLayer : public Layer{

		//todo fix acpect ration when changing camera aspect ratio.
		public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	public:
		OrthographicCameraController m_CameraController;


		Ref<Texture2D>m_CheckTexture;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = false;

		Ref<Framebuffer>m_FrameBuffer;
		glm::vec2 m_ViewportSize= {0.0f,0.0f};
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		SceneHierarchyPanel m_SceneHierarchyPanel;

	};



}

