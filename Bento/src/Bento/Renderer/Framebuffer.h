#pragma once
#include "Bento/Core/Core.h"

namespace Bento {

	enum class FramebufferTextureFormat {

		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/Stencil
		Depth24Stencil8,

		// Defaults
		Depth = Depth24Stencil8

	};

	struct FramebufferTextureSpecification {

		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}


		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap


	};

	struct FramebufferAttachmentSpecification {

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}


		std::vector<FramebufferTextureSpecification> Attachments;

	};

	struct FramebufferSpecification {

		uint32_t Width, Height;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
		// glBindFramebuffer(0)
	};

	class Framebuffer {

	public:
		virtual ~Framebuffer() = default;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual  const uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		 
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0; 

		virtual void ClearColorAttachment(uint32_t attachmentIndex, int value) = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	};

}