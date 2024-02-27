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

		void OnEvent(Event& e)override;

		void OnImGuiRender()override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	 	private:

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};

}