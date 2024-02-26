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

		float rotate = 0.0f;

		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture2D>m_CheckTexture;

		Ref<Framebuffer>m_FrameBuffer;



		Ref<Texture2D> m_SpriteSheet;

		// Ref<SubTexture2D> Ground[15][3];
		Ref<SubTexture2D> CurrentSubTexter;

		std::unordered_map<std::string, Ref<SubTexture2D>> s_TextureMap;

		

		OrthographicCameraController m_CameraController;

		glm::vec4 m_SquareColor = {0.45f, 0.354f, 0.783f, 1.0f};
		glm::vec4 m_SquareColor1 = {0.45f, 0.354f, 0.783f, 1.0f};

	};



}

