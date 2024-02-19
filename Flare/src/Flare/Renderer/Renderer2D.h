#pragma once

#include <Flare/Renderer/OrthographicCamera.h>

#include "Texture.h"

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

        // draw quad with color
        static void DrawQuad(const glm::vec2& position, const glm::vec2&size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2&size, const glm::vec4& color);

        // draw quad with texture
        static void DrawQuad(const glm::vec2& position, const glm::vec2&size, const Ref<Texture> texture, float tilingFactor = 1.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2&size, const Ref<Texture> texture, float tilingFactor = 1.0f);


        //draw quad with color + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        //draw quad with texture + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tailingFactor = 1.0f);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tailingFactor = 1.0f);

    };

}