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

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Spicification; }
		virtual const uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachments; }


	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachments, m_DepthAttachment;
		FramebufferSpecification m_Spicification;

	};

}