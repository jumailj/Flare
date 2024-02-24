#include "Sandbox2d.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


Sandbox2D::Sandbox2D()
    :Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, true)
{
  
}

void Sandbox2D::OnAttach() {
		m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");
		m_SpriteSheet = Flare::Texture2D::Create("Resource/game/sprteSheet.png");

		m_TextureStairs = Flare::SubTexture2D::CreateFromCoords(m_SpriteSheet, {2,1}, {128,128}, {1,2});
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
			rotate+=(15*ts);
			
			// Flare::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.8, 0.8f}, 50.0f, m_SquareColor1);
			// Flare::Renderer2D::DrawQuad({ 0.5f, -0.5f, 1.0f }, { 0.5f, 0.75f }, m_SquareColor1);
			// Flare::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckTexture, 5.0f);
			// Flare::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f },30.0f, m_SquareColor);
			//  Flare::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotate, m_CheckTexture, 1.0f);

			// size y is 2;. 32+32;
			Flare::Renderer2D::DrawQuad({0.0f, 0.0f,0.0f}, {1.0f, 2.0f}, m_TextureStairs);

			Flare::Renderer2D::EndScene();

/*

		Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.2f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.2f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
				Flare::Renderer2D::DrawRotatedQuad({ x, y }, { 0.2f, 0.2f },45.0f, color);
			}
		}
		Flare::Renderer2D::EndScene();

*/
		}
     
}

void Sandbox2D::OnImGuiRender() {

		ImGui::SetNextWindowBgAlpha(0.5f);

		ImGui::Begin("Settings");

		auto stats = Flare::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("indices: %d", stats.GetTotalIndexCount());

		ImGui::End();
  
		//ImGui::Begin("rotation");
		//ImGui::SliderFloat2("rotation", &rotate, 0.0f, 180.0f);
		//ImGui::End();
}

void Sandbox2D::OnEvent(Flare::Event& event) {
     m_CameraController.OnEvent(event);
}

