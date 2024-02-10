#include "RenderCommand.h"
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Flare{

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}