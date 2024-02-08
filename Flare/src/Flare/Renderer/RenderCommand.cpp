#include "RenderCommand.h"
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Flare{

    RendererAPI* RendereCommand::s_RendererAPI = new OpenGLRendererAPI;

}