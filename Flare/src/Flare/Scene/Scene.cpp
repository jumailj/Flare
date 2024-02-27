#include "Scene.h"

#include <glm/glm.hpp>

namespace Flare{

    Scene::Scene() 
    {
        struct TransformComponent
        {
            /* data */
            glm::mat4 Transform;

            TransformComponent() = default;
            TransformComponent(const TransformComponent&) = default; //copy-const
            TransformComponent(const glm::mat4& transform)
            :Transform(transform) {}

            operator const glm::mat4()  {return Transform;}
            operator const glm::mat4() const {return Transform;}

        };
        
        // uint32_t
        //add
        entt::entity enity = m_Registry.create();
        m_Registry.emplace<TransformComponent>(enity, glm::mat4(1.0f));


        // remove


    }

    Scene::~Scene() 
    {

    }



}