#include "Bentopch.h"
#include "RenderCommand.h"

#include "Bento/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bento {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}