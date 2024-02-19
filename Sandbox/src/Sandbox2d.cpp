#include "Sandbox2d.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


Sandbox2D::Sandbox2D()
    :Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, true)
{
    LOG_TRACE("small test for git");

		m_SquareVA = Flare::VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

        // new vertex buffer;
		Flare::Ref<Flare::VertexBuffer> squareVB;
		squareVB = Flare::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
			{ Flare::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);


        // new index buffer;
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Flare::Ref<Flare::IndexBuffer> squareIB;
		squareIB = Flare::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);


		m_FlatColorShader = (Flare::Shader::Create("Texture.glsl"));

}

void Sandbox2D::OnAttach() {
		m_CheckTexture = Flare::Texture2D::Create("check.png");
}

void Sandbox2D::OnDetach() {

}



void Sandbox2D::OnUpdate(Flare::Timestep ts) {
    // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		m_CameraController.OnUpdate(ts);


        //todo change to renderCommand
		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();


        Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Flare::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},m_SquareColor);
		Flare::Renderer2D::DrawQuad({0.5f, -0.5f}, {1.0f, 1.0f}, {0.234f, 0.534f, 0.23f, 1.0f});

		Flare::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.8f }, { 5.0f, 5.0f }, m_CheckTexture);
		



        Flare::Renderer2D::EndScene();

		// //todo add these functions shader::SetMat4, Sahder::setfloat4
		// 
		// 

}

void Sandbox2D::OnImGuiRender() {
    	// ImGui::Begin("settings");
		// ImGui::ColorEdit4("square color:", glm::value_ptr(m_SquareColor));
		// ImGui::End();
}

void Sandbox2D::OnEvent(Flare::Event& event) {
     m_CameraController.OnEvent(event);
}

