#pragma once

#include "Blaze/Renderer/Shader.h"

#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Blaze
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value) const;
		void UploadUniformInt2(const std::string& name, const glm::ivec2& vector) const;
		void UploadUniformInt3(const std::string& name, const glm::ivec3& vector) const;
		void UploadUniformInt4(const std::string& name, const glm::ivec4& vector) const;

		void UploadUniformTexture(const std::string& name, const int slot) const { UploadUniformInt(name, slot); }
		
		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const;
		
		void UploadUniformMat2(const std::string& name, const glm::mat2& matrix) const;
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}