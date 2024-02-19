#include "Sandbox2d.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


Sandbox2D::Sandbox2D()
    :Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, true)
{
  
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

      	Flare::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.7f, 0.5f, 1.3f, 1.0f });
		Flare::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 1.0f, 1.0f }, { 1.7f, 0.5f, 0.3f, 1.0f });
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

