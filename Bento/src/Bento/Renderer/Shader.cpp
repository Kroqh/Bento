#include "Bentopch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"


namespace Bento {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{		
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

