#pragma once

#include "Bento/Renderer/RendererAPI.h"
namespace Bento {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		OpenGLRendererAPI() {};

		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;
		virtual void SetLinesWidth(float width) override;

	};

}