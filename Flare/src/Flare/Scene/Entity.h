#pragma once


#include "Scene.h"
#include <entt.hpp>
#include <Flare/Core/Log.h>

#include <Flare/Core/UUID.h>
#include "Components.h"

namespace Flare{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if(HasComponent<T>()){LOG_ERROR("Entity already have Component!");}
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			if(!HasComponent<T>()){	LOG_ERROR("Entity does not have Component!");}
			
			//possible to crash the program.
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			if(!HasComponent<T>()){LOG_ERROR("Entity does not have Component!");}
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		// to destory entity.
		operator entt::entity() const {return m_EntityHandle;}

		//get he uuid for the object.
		UUID GetUUID() { return GetComponent<IDComponent>().ID;}
		
		// get the current object tag name;
		std::string GetName() {return GetComponent<TagComponent>().Tag;}

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};


}