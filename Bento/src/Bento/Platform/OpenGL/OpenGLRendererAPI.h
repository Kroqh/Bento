#pragma once

#include "Bento/Renderer/RendererAPI.h"
namespace Bento {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		OpenGLRendererAPI() {};
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}