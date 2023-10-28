﻿#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Blaze
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec4);
		void UploadUniformMat4(const std::string& name, const glm::mat4& mat4);
	private:
		uint32_t m_RendererID;
	};
}