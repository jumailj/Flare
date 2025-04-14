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
		m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");
}

void Sandbox2D::OnDetach() {

}


void Sandbox2D::OnUpdate(Flare::Timestep ts) {
    // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		m_CameraController.OnUpdate(ts);

		//Render 
		Flare::Renderer2D::ResetStats();
		{
			Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Flare::RenderCommand::Clear();
		}


		{
			Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
			
			Flare::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckTexture, 5.0f);



			if ( Flare::Input::IsKeyPressed(Flare::Key::A)) {
				LOG_WARN("hello world");
			}
			Flare::Renderer2D::EndScene();
		}
     
}

void Sandbox2D::OnImGuiRender() 
{

				ImGui::SetNextWindowBgAlpha(0.5f);
				ImGui::Begin("Settings");
				auto stats = Flare::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("indices: %d", stats.GetTotalIndexCount());

				ImGui::End();
}


void Sandbox2D::OnEvent(Flare::Event& event) {
     m_CameraController.OnEvent(event);
}

