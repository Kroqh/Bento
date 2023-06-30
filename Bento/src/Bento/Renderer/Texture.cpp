#include "Bentopch.h"
#include "Texture.h"

#include "Bento/Renderer/Renderer.h"
#include "Bento/Platform/OpenGL/OpenGLTexture.h"

namespace Bento {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     BENTO_CORE_ASSERT(false, " RendererAPI::None is not surrported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
		}
		BENTO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}