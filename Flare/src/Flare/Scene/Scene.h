#pragma once

#include <entt.hpp>
#include <Flare/Core/UUID.h>
#include <Flare/Core/Timestep.h>
#include <Flare/Renderer/EditorCamera.h>

class b2World;

namespace Flare{

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid,const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

	
		void DuplicateEntity(Entity entity);

		Entity GetEntityByUUID(UUID uuid);
		Entity GetPrimaryCameraEntity();

		
		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}


	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void RenderScene(EditorCamera& camera);



	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		b2World* m_PhysicsWorld = nullptr;

		std::unordered_map<UUID, Entity> m_EntityMap;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}