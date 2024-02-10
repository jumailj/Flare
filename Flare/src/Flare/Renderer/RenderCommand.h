#pragma once

#include "RendererAPI.h"

namespace Flare{

    class RenderCommand
    {

    public:

        inline static void SetClearColor(const glm::vec4& color) 
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() 
        {
            // don't sure about is why it's not working..
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray> & vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:

        static RendererAPI * s_RendererAPI;


    };


}