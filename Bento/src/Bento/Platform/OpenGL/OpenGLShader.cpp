#include "Bentopch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Bento {

	static GLenum ShaderTypeFromString(const std::string& type) {
		BENTO_PROFILE_FUNCTION();
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		BENTO_CORE_ASSERT(false, "Unknown shader type!");

	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		BENTO_PROFILE_FUNCTION();
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		//Example:
		// assets/shaders/Textures.glsl
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		BENTO_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		BENTO_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}
	 
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		BENTO_PROFILE_FUNCTION();
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			BENTO_CORE_ERROR("Could not open gile '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		BENTO_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {

			size_t eol = source.find_first_of("\r\n", pos);
			BENTO_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			BENTO_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		BENTO_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		BENTO_CORE_ASSERT(shaderSources.size() <= 2, "More than two shaders! (API only supports 2 shaders)");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources) {

			GLenum type = kv.first;
			const std::string& source = kv.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				BENTO_CORE_ERROR("{0}", infoLog.data());
				BENTO_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;
		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			BENTO_CORE_ERROR("{0}", infoLog.data());
			BENTO_CORE_ASSERT(false, "Program linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}

	void OpenGLShader::Bind() const
	{
		BENTO_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		BENTO_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float value)
	{
		BENTO_PROFILE_FUNCTION();
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(loc, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(loc, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(loc, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec2)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(loc, vec2.x, vec2.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec3)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(loc, vec3.x, vec3.y, vec3.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec4)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(loc, vec4.x, vec4.y, vec4.z, vec4.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint loc = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	
	

}