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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearColorAttachment(uint32_t attachmentIndex, int value) override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual const uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{ 
			BENTO_CORE_ASSERT("'index' is larger than 'm_ColorAttachments'",index < m_ColorAttachments.size());
			return m_ColorAttachments[index]; 
		}


	private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;
		FramebufferTextureSpecification m_DepthAttachmentSpec;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;

	};

}