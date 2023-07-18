#include "Bentopch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bento {

	struct Renderer2DStorage {

		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> m_DefaultTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		BENTO_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();

		s_Data->m_DefaultTexture = Texture2D::Create(1,1);
		uint32_t defaultTextureData = 0xffffffff;
		s_Data->m_DefaultTexture->SetData(&defaultTextureData,sizeof(uint32_t));

		s_Data->QuadVertexArray = VertexArray::Create();


		float squareVertices[(4 * 3) + (2*4)] = {

			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		};


		Ref<VertexBuffer> sqaureVB;
		sqaureVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout layout2 = {

			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},

		};

		sqaureVB->SetLayout(layout2);
		s_Data->QuadVertexArray->AddVertexBuffer(sqaureVB);

		unsigned int squareIndices[6] = {
			0,1,2,
			2,3,0
		};

		Ref<IndexBuffer> sqaureIB;
		sqaureIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		s_Data->QuadVertexArray->SetIndexBuffer(sqaureIB);

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		BENTO_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		BENTO_PROFILE_FUNCTION();
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetVPMatrix());
		
	}

	void Renderer2D::EndScene()
	{
		BENTO_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		BENTO_PROFILE_FUNCTION();
		s_Data->TextureShader->SetFloat4("u_Color", color);

		// Bind white texture
		s_Data->m_DefaultTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x,position.y,position.z });
		transform = glm::scale(transform, { size.x, size.y, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x,position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		BENTO_PROFILE_FUNCTION();
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x,position.y,position.z });
		transform = glm::scale(transform, { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}