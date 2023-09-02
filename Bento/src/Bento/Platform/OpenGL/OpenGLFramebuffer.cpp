#include "Bentopch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Bento {

	namespace Utils {

		static GLenum TextureTarget(bool multisampled) {
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count) {

			glCreateTextures(TextureTarget(multisampled), count, outID);

		}

		static void BindTexture(bool multisampled, uint32_t id) {

			glBindTexture(TextureTarget(multisampled), id);

		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat,GLenum format, uint32_t width, uint32_t height, int index) {

			bool multisampled = samples > 1;
			if (multisampled) {

				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);

			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				// TODO: Filtering/wrap modes
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}
		static void AttachDepthTexture(uint32_t id, int samples, GLenum format,GLenum attachmentType, uint32_t width, uint32_t height) {

			bool multisampled = samples > 1;
			if (multisampled) {

				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);

			}
			else {
				glTexStorage2D(GL_TEXTURE_2D, samples, format, width, height);

				// TODO: Filtering/wrap modes
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format) {

			switch (format) {
				case FramebufferTextureFormat::Depth24Stencil8: return true;
			}

			return false;

		}

		static GLenum BentoFBTextureFormatToGL(FramebufferTextureFormat format) {

			switch (format) {
			case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			BENTO_CORE_ASSERT("Unknown format!", false);
			return 0;

		}

		static GLenum GLDataType(FramebufferTextureFormat format) {

			switch (format) {
			case FramebufferTextureFormat::RGBA8:       return GL_UNSIGNED_INT;
			case FramebufferTextureFormat::RED_INTEGER: return GL_INT;
			}

			BENTO_CORE_ASSERT("Unknown format!", false);
			return 0;

		}
	}

	

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{

		for (auto format : m_Specification.Attachments.Attachments) {

			if (!Utils::IsDepthFormat(format.TextureFormat))
				m_ColorAttachmentSpecs.emplace_back(format);
			else
				m_DepthAttachmentSpec = format;

		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID) {

			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);


		
		bool multisample = m_Specification.Samples > 1;
		// Attachments
		if (m_ColorAttachmentSpecs.size()) {

			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());
			for (size_t i = 0; i < m_ColorAttachments.size(); i++) {

				Utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecs[i].TextureFormat) {
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
					break;
				}
			}
		}
		
		if (m_DepthAttachmentSpec.TextureFormat != FramebufferTextureFormat::None) {
			Utils::CreateTextures(multisample, &m_DepthAttachment, 1);
			Utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpec.TextureFormat)
			{
			case FramebufferTextureFormat::Depth24Stencil8:

				Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, 
					GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
					m_Specification.Width, m_Specification.Height);

				break;
			}
		}

		if (m_ColorAttachments.size() > 1) {

			BENTO_CORE_ASSERT("'m_ColorAttachments' can't go over 4", m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);

		}
		else if(m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		BENTO_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);

	}

	void OpenGLFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		BENTO_CORE_ASSERT("Attachment index can't be larger than 'm_ColorAttachments.size()'", attachmentIndex < m_ColorAttachments.size());
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);

		return pixelData;
	}

	void OpenGLFramebuffer::ClearColorAttachment(uint32_t attachmentIndex, int value)
	{
		BENTO_CORE_ASSERT("Attachment index can't be larger than 'm_ColorAttachments.size()'", attachmentIndex < m_ColorAttachments.size());


		//int value = -1;
		//glClearTexImage(m_ColorAttachments[1], 0, GL_RED_INTEGER, GL_INT, &value);

		auto& spec = m_ColorAttachmentSpecs[attachmentIndex];

		glClearTexImage(m_ColorAttachments[attachmentIndex], 0, Utils::BentoFBTextureFormatToGL(spec.TextureFormat), Utils::GLDataType(spec.TextureFormat), &value);
	}

}