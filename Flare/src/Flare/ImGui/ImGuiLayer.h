#pragma once

#include <Flare/Core/Layer.h>
#include <Flare/Events/ApplicationEvent.h>
#include <Flare/Events/KeyEvent.h>
#include <Flare/Events/MouseEvent.h>

namespace Flare {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		 virtual void OnAttach()override;
		 virtual void OnDetach()override;
		// virtual void OnUpdate()override;

		//  void OnEvent(Event& e);

		void OnImGuiRender()override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		// events- temp-fro now
	 	private:
	 	// bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		// bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		// bool OnMouseMovedEvent(MouseMovedEvent& e);
		// bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		// bool OnKeyPressedEvent(KeyPressedEvent& e);
		// bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	    // bool OnKeyTypedEvent(KeyTypedEvent& e);
		// bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};

}