#pragma once 

#include <Flare/Renderer/Shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace Flare
{
    class OpenGLShader: public Shader{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind()const override;
		void Unbind() const override;

		void SetInt(const std::string& name,  int value ) override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void SetFloat(const std::string&name,  float value) override;
		void SetFloat2(const std::string&name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value)override;
		void SetFloat4(const std::string &name, const glm::vec4& value) override;

		void SetMat3(const std::string&name, const glm::mat3& matrix) override;
		void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual const std::string& GetName() const override {return m_Name;}

		/*opengl specific*/
		void UploadUniformInt(const std::string& name, const int& value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, const float& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);


		
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		
		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);

		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;

	};
    
} // namespace Flare


