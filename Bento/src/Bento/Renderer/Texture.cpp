#include "Bentopch.h"
#include "Texture.h"

#include "Bento/Renderer/Renderer.h"
#include "Bento/Platform/OpenGL/OpenGLTexture.h"

namespace Bento {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		BENTO_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLTexture2D>(width, height);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		BENTO_PROFILE_FUNCTION();
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return CreateRef<OpenGLTexture2D>(path);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}