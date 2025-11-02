#include "Sandbox2d.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// for networking , (http);
#include "httplib.h"

Sandbox2D::Sandbox2D()
    :Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, false)
{
  
}

void Sandbox2D::OnAttach() 
{
		m_CheckTexture = Flare::Texture2D::Create("Resource/check.png");
		m_player = Flare::Texture2D::Create("Resource/player.png");
		/* load the font*/
		m_Font = Flare::Font::GetDefault();


		//networking code..

		/*

		httplib::Client cli("http://127.0.0.1:3000");
		auto res = cli.Get("/api/data");

		LOG_INFO("status{0}", res->status);
		m_DataString = res->body;
		*/



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
			// Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
			Flare::Renderer2D::BeginScene(m_CameraController.GetCamera());
			


			// Flare::Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckTexture, 0.0f);
			Flare::Renderer2D::DrawQuad(playerPos, {1.0f, 1.0f}, m_player, 1.0f);


			// Add text rendering here - similar to how you draw quads
			glm::mat4 textTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			// Flare::Renderer2D::DrawString("Hello Sandbox!", m_Font, textTransform, {glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)});

			// Flare::Renderer2D::DrawString(m_DataString.c_str(), m_Font, textTransform, {glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)});

			// You can also draw text at different positions
			// glm::mat4 textTransform2 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0wd.0f));
			

			//Flare::Renderer2D::DrawString("hello world", m_Font, {0,0,0}, 1, *textComponet);



			for (int x =1;  x< 10; x++) {
				for (int y = 1; y < 10; y++) {
					// Flare::Renderer2D::DrawRotatedQuad({x, y}, 2.8f, {1.0f, 1.0f}, m_player, 1.0f );
					Flare::Renderer2D::DrawRotatedQuad({x,y}, {1.0f, 1.0f}, rotation, m_player, 1);
				}
			}

			rotation++;



			if ( Flare::Input::IsKeyPressed(Flare::Key::Up)) {
				playerPos.y += 5.0f* ts;
			}




			Flare::Renderer2D::EndScene();
		}
     
}

void Sandbox2D::OnImGuiRender() 
{

				ImGui::SetNextWindowBgAlpha(0.5f);
				ImGui::Begin("Stats");
				auto stats = Flare::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("indices: %d", stats.GetTotalIndexCount());

				ImGui::Text("%s", m_DataString.c_str());
				

				ImGui::End();
}


void Sandbox2D::OnEvent(Flare::Event& event) {
     m_CameraController.OnEvent(event);
}

