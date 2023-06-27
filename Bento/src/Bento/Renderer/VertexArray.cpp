#include "Bentopch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Bento/Platform/OpenGL/OpenGLVertexArray.h"

namespace Bento {



	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}