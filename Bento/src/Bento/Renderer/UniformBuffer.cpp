#include "Bentopch.h"
#include "UniformBuffer.h"

#include "Bento/Renderer/Renderer.h"
#include "Bento/Platform/OpenGL/OpenGLUniformBuffer.h"
namespace Bento {
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BENTO_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

