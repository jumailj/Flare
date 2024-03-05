#pragma once
#pragma once

// #include <yaml-cpp/yaml.h>
#include <Flare/Core/Core.h>
#include "Scene.h"

namespace Flare{
    
    class SceneSerializer
    {
     public:
        SceneSerializer(const Ref<Scene>& scene);

        void Serialize(const std::string& filepath);
        void SerializeRuntime(const std::string& filepath); // into binary

        bool Deserialize(const std::string& filepath);
        bool DeserializeRuntime(const std::string& filepath); // into binary

    private:
        Ref<Scene> m_Scene;
    };


}
