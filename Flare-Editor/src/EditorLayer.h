#pragma once

#include <Flare/Core/Flare.h>

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

		float rotate = 0.0f;

		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture2D>m_CheckTexture;

		Ref<Scene> m_ActiveScene;
		entt::entity m_SquareEntity;

		Ref<Framebuffer>m_FrameBuffer;
		glm::vec2 m_ViewportSize= {0.0f,0.0f};
		bool m_ViewportFocused = false, m_ViewportHovered = false;


		Ref<Texture2D> m_SpriteSheet;

		// Ref<SubTexture2D> Ground[15][3];
		Ref<SubTexture2D> CurrentSubTexter;

		std::unordered_map<std::string, Ref<SubTexture2D>> s_TextureMap;	



	};



}

