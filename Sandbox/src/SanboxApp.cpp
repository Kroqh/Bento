#include <Bento.h>

#include "imgui/imgui.h"


class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({0.0f,0.0f, 0.0f}) {
		
		// Vertex array
		m_VertexArray.reset(Bento::VertexArray::Create());
		// Index Buffer

		float vertices[(3 * 3) + (4 * 4)] = {

			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f

		};

		// Vertex Buffer
		std::shared_ptr<Bento::VertexBuffer> m_VertexBuffer;
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

		std::shared_ptr<Bento::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Bento::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(Bento::VertexArray::Create());


		float squareVertices[(4 * 3)] = {

			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f

		};


		std::shared_ptr<Bento::VertexBuffer> sqaureVB;
		sqaureVB.reset(Bento::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Bento::BufferLayout layout2 = {

			{Bento::ShaderDataType::Float3, "a_Position"},

		};
		
		sqaureVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(sqaureVB);

		unsigned int squareIndices[6] = {
			0,1,2,
			2,3,0
		};

		std::shared_ptr<Bento::IndexBuffer> sqaureIB;
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

		m_Shader.reset(new Bento::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
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

			void main()
			{
				color = vec4(0.3, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader2.reset(new Bento::Shader(vertexSrc2, fragmentSrc2));

		
	}
	 
	void OnUpdate(Bento::Timestep ts) override{

		BENTO_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Bento::Input::IsKeyPressed(Bento::Key::A))
			m_CameraPosition.x -= m_CameraSpeed * ts;

		if (Bento::Input::IsKeyPressed(Bento::Key::D))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (Bento::Input::IsKeyPressed(Bento::Key::W))
			m_CameraPosition.y += m_CameraSpeed * ts;

		if (Bento::Input::IsKeyPressed(Bento::Key::S))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		if (Bento::Input::IsKeyPressed(Bento::Key::E))
			m_CameraRotation -= m_CameraTurnRate * ts;

		if (Bento::Input::IsKeyPressed(Bento::Key::Q))
			m_CameraRotation += m_CameraTurnRate * ts;

		Bento::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Bento::RenderCommand::Clear();

		m_Camera.SetPositon(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Bento::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (size_t y = 0; y < 20; y++)
		{
			for (size_t x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Bento::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}

		
		Bento::Renderer::Submit(m_Shader, m_VertexArray);

		Bento::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {

		

	}
	void OnEvent(Bento::Event& event) override {

		Bento::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Bento::KeyPressedEvent>(BENTO_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

		if (event.GetEventType() == Bento::EventType::KeyPressed) {

			Bento::KeyPressedEvent& e = (Bento::KeyPressedEvent&)event;

			if (e.GetKeyCode() == Bento::Key::H && e.GetRepeatCount() == 0) {
				BENTO_TRACE("{0}", (char)e.GetKeyCode());
			}

		}

	}

	bool OnKeyPressedEvent(Bento::KeyPressedEvent& event) {

		


		return false;

	}

private:
	std::shared_ptr<Bento::VertexArray> m_VertexArray;
	std::shared_ptr<Bento::Shader> m_Shader;

	std::shared_ptr<Bento::VertexArray> m_SquareVA;
	std::shared_ptr<Bento::Shader> m_Shader2;

	Bento::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraSpeed = 5.0f;
	float m_CameraTurnRate =90.0f;

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