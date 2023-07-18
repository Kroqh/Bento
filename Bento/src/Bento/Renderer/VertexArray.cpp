#include "Bentopch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Bento/Platform/OpenGL/OpenGLVertexArray.h"

namespace Bento {



	Ref<VertexArray> VertexArray::Create()
	{
		BENTO_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexArray>();
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}