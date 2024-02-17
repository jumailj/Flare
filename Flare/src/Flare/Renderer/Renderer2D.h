#pragma once

#include <Flare/Renderer/OrthographicCamera.h>
// super static class, no data storage.
namespace Flare{

    class Renderer2D
    {

    public:

        static void Init();
        static void ShutDown();
        static void BeginScene(const OrthographicCamera & camera);
        static void EndScene();

        //primitives;
        static void DrawQuad(const glm::vec2& position, const glm::vec2&size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2&size, const glm::vec4& color);
    };

}