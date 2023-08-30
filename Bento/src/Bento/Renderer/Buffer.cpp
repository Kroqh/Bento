#include "Bentopch.h"
#include "Buffer.h"
#include "Bento/Renderer/Renderer.h"

#include "Bento/Platform/OpenGL/OpenGLBuffer.h"

namespace Bento {



	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		BENTO_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return  CreateRef<OpenGLVertexBuffer>(size);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		BENTO_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		BENTO_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	

}