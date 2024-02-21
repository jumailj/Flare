#include "RenderCommand.h"
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Flare{

  Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}