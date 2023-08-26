#pragma once

#include "Bento/Renderer/Framebuffer.h"

namespace Bento {

	class OpenGLFramebuffer : public Framebuffer {

	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual const uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachments; }


	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachments = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;

	};

}