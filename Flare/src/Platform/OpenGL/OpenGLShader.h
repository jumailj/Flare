#pragma once 

#include <Flare/Renderer/Shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Flare
{
    class OpenGLShader: public Shader{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind()const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int value ) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;
		void SetFloat4(const std::string &name, const glm::vec4& value) override;


		virtual const std::string& GetName() const override {return m_Name;}

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);


		
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
		std::string m_Name;

	};
    
} // namespace Flare


