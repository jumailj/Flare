#pragma once

#include <Flare/Renderer/OrthographicCamera.h>

#include <Flare/Renderer/Texture.h>
#include <Flare/Renderer/SubTexture2D.h>
#include <Flare/Renderer/Camera.h>
#include <Flare/Renderer/EditorCamera.h>

// super static class, no data storage.
namespace Flare{

    class Renderer2D
    {
    public:


        static void Init();
        static void ShutDown();

        static void BeginScene(const Camera& camera, const glm::mat4 transform); 
        static void BeginScene(const EditorCamera& camera);
        static void BeginScene(const OrthographicCamera & camera); // todo remove
        static void EndScene();
        static void Flush();

        //primitives;

        //non-rotatable;

        // draw quad with color
        static void DrawQuad(const glm::vec2& position, const glm::vec2&size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2&size, const glm::vec4& color);
        // draw quad with texture
        static void DrawQuad(const glm::vec2& position, const glm::vec2&size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f,  const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2&size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f,  const glm::vec4& tintColor = glm::vec4(1.0f));
        // draw quad with transform with color
        static void DrawQuad(const glm::mat4 transform, const glm::vec4& color);
       

        //rotatable;
        
        //draw quad with color + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        //draw quad with texture + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        // draw quad with transform with texture
        static void DrawQuad(const glm::mat4 transform , const Ref<Texture2D>&texture, float tilingFactor= 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));


        //stats;
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() {return QuadCount*4;}
			uint32_t GetTotalIndexCount() {return QuadCount*6;}

		};

		static void ResetStats();
        static Statistics GetStats();

    private:
        static void FlushAndReset();    

    };

}