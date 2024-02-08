
#include "Renderer.h"

namespace Flare{

    void Renderer::BeginScene() 
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RendereCommand::DrawIndexed(vertexArray);
    }

   
}