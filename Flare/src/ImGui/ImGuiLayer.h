#pragma once

#include <Core/Layer.h>

#include <Events/ApplicationEvent.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

namespace Flare {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		 void OnAttach();
		 void OnDetach();
		 void OnEvent(Event& e);
		 void OnUpdate();
		 void OnImGuiRender();

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		// events- temp-fro now
	 	private:
	 	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	   // bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};
}