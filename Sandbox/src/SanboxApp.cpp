#include <Bento.h>


#include "Bento/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>




class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example"), m_CameraController( 1920.0f / 1080.0f, true), m_CameraPosition({0.0f,0.0f, 0.0f}) {

		// Vertex array
		m_VertexArray.reset(Bento::VertexArray::Create());
		// Index Buffer

		float vertices[(3 * 3) + (4 * 4)] = {

			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f

		};

		// Vertex Buffer
		Bento::Ref<Bento::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Bento::VertexBuffer::Create(vertices, sizeof(vertices)));

		Bento::BufferLayout layout = {

			{Bento::ShaderDataType::Float3, "a_Position"},
			{Bento::ShaderDataType::Float4, "a_Color"},

		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = {
			0,1,2
		};

		Bento::Ref<Bento::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Bento::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(Bento::VertexArray::Create());


		float squareVertices[(4 * 3) + (2*4)] = {

			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		};


		Bento::Ref<Bento::VertexBuffer> sqaureVB;
		sqaureVB.reset(Bento::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Bento::BufferLayout layout2 = {

			{Bento::ShaderDataType::Float3, "a_Position"},
			{Bento::ShaderDataType::Float2, "a_TexCoord"},

		};
		
		sqaureVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(sqaureVB);

		unsigned int squareIndices[6] = {
			0,1,2,
			2,3,0
		};

		Bento::Ref<Bento::IndexBuffer> sqaureIB;
		sqaureIB.reset(Bento::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(sqaureIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;	
			uniform mat4 u_Transform;		

			out vec3 v_Position;
			out vec4 v_color;

			void main()
			{
				v_color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";
		std::string fragmentSrc = R"(
		
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_color;
			void main()
			{
				color = v_color;
			}
		)";

		m_Shader = Bento::Shader::Create("Shader", vertexSrc, fragmentSrc);
		m_ShaderLibrary.Add(m_Shader);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
		    layout(location = 1) in vec2 a_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";
		std::string fragmentSrc2 = R"(
		
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader2 = Bento::Shader::Create("Shader2",vertexSrc2, fragmentSrc2);
		m_ShaderLibrary.Add(m_Shader2);
		

		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Bento::Texture2D::Create("assets/textures/Checkerboard.png");
		m_AmongUsTexture = Bento::Texture2D::Create("assets/textures/AmongUsCharacter.png");

		std::dynamic_pointer_cast<Bento::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->Bind();
		std::dynamic_pointer_cast<Bento::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);
	}
	 
	void OnUpdate(Bento::Timestep ts) override{

		// Update
		m_CameraController.OnUpdate(ts);

		// Render

		BENTO_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		
		Bento::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Bento::RenderCommand::Clear();

		

		Bento::Renderer::BeginScene(m_CameraController.GetCamera());

		

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Bento::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Bento::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);
		for (size_t y = 0; y < 20; y++)
		{
			for (size_t x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Bento::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}
		m_Texture->Bind();
		Bento::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_AmongUsTexture->Bind();
		Bento::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::translate(glm::mat4(1.0f), m_AmongUsPosition) *
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		//Bento::Renderer::Submit(m_Shader, m_VertexArray);
		
		Bento::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::DragFloat3("Among Us Transform", glm::value_ptr(m_AmongUsPosition), 0.1f);
		ImGui::End();

		

	}
	void OnEvent(Bento::Event& e) override {

		m_CameraController.OnEvent(e);

		Bento::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Bento::KeyPressedEvent>(BENTO_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

		if (e.GetEventType() == Bento::EventType::KeyPressed) {

			Bento::KeyPressedEvent& KeyPressedEvent = (Bento::KeyPressedEvent&)e;

			if (KeyPressedEvent.GetKeyCode() == Bento::Key::H && KeyPressedEvent.GetRepeatCount() == 0) {
				BENTO_TRACE("{0}", (char)KeyPressedEvent.GetKeyCode());
			}

		}

	}

	bool OnKeyPressedEvent(Bento::KeyPressedEvent& event) {
		return false;

	}

	

private:
	Bento::ShaderLibrary m_ShaderLibrary;
	Bento::Ref<Bento::VertexArray> m_VertexArray;
	Bento::Ref<Bento::Shader> m_Shader;

	Bento::Ref<Bento::VertexArray> m_SquareVA;
	Bento::Ref<Bento::Shader> m_Shader2;

	Bento::Ref<Bento::Texture2D> m_Texture, m_AmongUsTexture;

	Bento::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_AmongUsPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_SquareColor = glm::vec3(0.3f, 0.3f, 0.8f);
};

class Sandbox : public Bento::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new Sandbox();
}