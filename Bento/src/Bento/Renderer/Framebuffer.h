#pragma once
#include "Bento/Core/Core.h"

namespace Bento {

	struct FramebufferSpecification {

		uint32_t Width, Height;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
		// glBindFramebuffer(0)
	};

	class Framebuffer {

	public:
		virtual ~Framebuffer() = default;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual  const uint32_t GetColorAttachmentRendererID() const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	};

}