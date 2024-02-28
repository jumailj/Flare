#pragma once

#include <entt.hpp>
#include <Flare/Core/Timestep.h>

namespace Flare{

	class Scene 
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		//temp;
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
			entt::registry m_Registry; // identifier-actual component data;

	};

}