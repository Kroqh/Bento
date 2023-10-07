#pragma once

#include "RendererAPI.h"

namespace Bento {

	class RenderCommand {

	public:
		inline static void Init() {
			BENTO_PROFILE_FUNCTION();
			s_RendererAPI->Init();

		}

		inline static void Clear() {

			s_RendererAPI->Clear();

		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

			s_RendererAPI->SetViewport(x, y, width, height);

		}

		inline static void SetClearColor(const glm::vec4& color) {

			s_RendererAPI->SetClearColor(color);

		}
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {

			s_RendererAPI->DrawIndexed(vertexArray, indexCount);

		}
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {

			s_RendererAPI->DrawIndexed(vertexArray);

		}
		inline static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) {

			s_RendererAPI->DrawLines(vertexArray, vertexCount);

		}
		inline static void SetLineWidth(float width) {

			s_RendererAPI->SetLinesWidth(width);

		}
	private:
		static RendererAPI* s_RendererAPI;

	};

}