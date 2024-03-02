#pragma once

#include <Flare/Scene/Scene.h>
#include <Flare/Core/Core.h>
#include <Flare/Scene/Entity.h>
#include <Flare/Core/Log.h>


namespace Flare{


	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}