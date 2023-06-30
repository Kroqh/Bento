#include "Bentopch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"


namespace Bento {


	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(filepath);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{		
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		BENTO_CORE_ASSERT(!Exits(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		BENTO_CORE_ASSERT(!Exits(name), "Shader already exists!");
		m_Shaders[name] = shader;
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
		BENTO_CORE_ASSERT(Exits(name), "Shader not found!")
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exits(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}

