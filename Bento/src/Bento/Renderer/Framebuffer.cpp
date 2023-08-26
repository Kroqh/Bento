#include "Bentopch.h"
#include "Framebuffer.h"

#include "Bento/Renderer/Renderer.h"

#include "Bento/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Bento {

	Ref<Framebuffer> Bento::Framebuffer::Create(const FramebufferSpecification& spec)
	{
		BENTO_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLFramebuffer>(spec);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}


