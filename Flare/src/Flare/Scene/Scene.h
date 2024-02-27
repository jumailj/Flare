#pragma once

#include<entt.hpp>

namespace Flare{

    class Scene
    {
    public:
        Scene();
        ~Scene();

    private:
        /*entity, is identifier which used to determite which components belogs together*/
        /*registry, is actual component data.(context)*/
        entt::registry m_Registry;

    };


}