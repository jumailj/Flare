#include "UniformBuffer.h"

#include<Flare/Renderer/Renderer.h>
#include<Platform/OpenGL/OpenGLUniformBuffer.h>


namespace Flare {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG_ERROR("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

        LOG_ERROR("Unknown RendererAPI!");
		return nullptr;
	}

}