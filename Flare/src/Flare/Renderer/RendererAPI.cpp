#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Flare{

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    	Scope<RendererAPI> RendererAPI::Create()
	{
		
		switch (s_API)
		{
		case RendererAPI::API::None:    LOG_ERROR( "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		LOG_ERROR("Unknown RendererAPI!");
		return nullptr;
	}

}