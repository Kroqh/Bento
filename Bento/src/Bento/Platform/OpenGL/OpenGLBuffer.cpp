#include "Bentopch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Bento {

	// Vertex Buffer ///////////////////////////////////////////////////////////////////////////////

#pragma region VertexBuffer
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		BENTO_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		Bind();

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		BENTO_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		Bind();

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		BENTO_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		BENTO_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		BENTO_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
#pragma endregion

	// Index Buffer ///////////////////////////////////////////////////////////////////////////////

#pragma region IndexBuffer
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		BENTO_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		Bind();
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		BENTO_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		BENTO_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		BENTO_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
#pragma endregion

	

	

	

}