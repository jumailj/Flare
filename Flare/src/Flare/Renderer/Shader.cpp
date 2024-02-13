#include "Shader.h"

#include "Renderer.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace Flare{

	Ref<Shader> Shader::Create(const std::string& filepath) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LOG_ERROR("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
		}
		 LOG_ERROR("[shader] Unknown RendereAPI");
		return nullptr;
		
	}
    
	Ref<Shader>Shader::Create( const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LOG_ERROR("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

        LOG_ERROR("[shader] Unknown RendereAPI");
        return nullptr;

    }

	// -------- shader library -------   //

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	 {
		m_Shaders[name] = shader;
	 }

	 void ShaderLibrary::Add(const Ref<Shader>&shader)
	 {
		auto& name = shader->GetName();
		Add(name, shader);
	 }


	 Ref<Shader> ShaderLibrary::Load(const std::string& filepath) 
	 {
			auto shader = Shader::Create(filepath);
			Add(shader);
			return shader;
	 }

	 Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) 
	 {
			auto shader = Shader::Create(filepath);
			Add(name, shader);
			return shader;

	 }

	 Ref<Shader> ShaderLibrary::Get(const std::string& name)
	 {
			return m_Shaders[name];
	 }

}