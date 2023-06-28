#pragma once
#include "Bento/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Bento {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec2);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec3);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec4);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		
	
	private:
		uint32_t m_RendererID;


	};

}