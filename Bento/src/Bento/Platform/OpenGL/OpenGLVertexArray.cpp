#include "Bentopch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Bento {


	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {

		switch (type)
		{
		 case Bento::ShaderDataType::Float:	 return GL_FLOAT;
		 case Bento::ShaderDataType::Float2:  return GL_FLOAT;
		 case Bento::ShaderDataType::Float3:  return GL_FLOAT;
		 case Bento::ShaderDataType::Float4:  return GL_FLOAT;
		 case Bento::ShaderDataType::Mat3:	 return GL_FLOAT;
		 case Bento::ShaderDataType::Mat4:	 return GL_FLOAT;
		 case Bento::ShaderDataType::Int:	 return GL_INT;
		 case Bento::ShaderDataType::Int2:	 return GL_INT;
		 case Bento::ShaderDataType::Int3:	 return GL_INT;
		 case Bento::ShaderDataType::Int4:	 return GL_INT;
		 case Bento::ShaderDataType::Bool:	 return GL_BOOL;
		}

		BENTO_CORE_ASSERT(false, "Unknown ShaderDataType!");

		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		BENTO_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		BENTO_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		BENTO_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		BENTO_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		BENTO_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		BENTO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "bertexBuffer in 'OpenGLVertexArray.cpp' has no layout!")

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);

			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		BENTO_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}