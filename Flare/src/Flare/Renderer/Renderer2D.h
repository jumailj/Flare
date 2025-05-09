#pragma once

#include <Flare/Renderer/OrthographicCamera.h>
#include <Flare/Renderer/Texture.h>
#include <Flare/Renderer/Camera.h>
#include <Flare/Renderer/EditorCamera.h>

#include <Flare/Scene/Components.h>


// super static class, no data storage.
namespace Flare{

    class Renderer2D
    {
    public:


        static void Init();
        static void Shutdown();

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
        static void DrawQuad(const glm::mat4 transform, const glm::vec4& color, int entityID =-1);
       
        //rotatable;
        
        //draw quad with color + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        //draw quad with texture + rotatable
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        // draw quad with transform with texture
        static void DrawQuad(const glm::mat4 transform , const Ref<Texture2D>&texture, float tilingFactor= 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);


        static void DrawSprite(const glm::mat4& transfrom, SpriteRendererComponent& src, int entityID);

        // new circle rendere fuction;
        static void DrawCircle(const glm::mat4& transfrom, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);

        //draw line rendering functions;

		static void DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);

        // test code.
        static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, int entityID = -1);

		static float GetLineWidth();
		static void SetLineWidth(float width);


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

        static void StartBatch();
        static void NextBatch();

    };

}