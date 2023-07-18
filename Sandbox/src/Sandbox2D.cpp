#include "Sandbox2D.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{
	
}

void Sandbox2D::OnAttach()
{
	BENTO_PROFILE_FUNCTION();
	m_Texture = Bento::Texture2D::Create("assets/textures/Checkerboard.png");
	
}

void Sandbox2D::OnDeAttach()
{
	BENTO_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Bento::Timestep ts)
{
	BENTO_PROFILE_FUNCTION();

	// Update
	{
		BENTO_PROFILE_SCOPE("OrthographicCameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	

	// Render
	{
		BENTO_PROFILE_SCOPE("Renderer prep");
		Bento::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Bento::RenderCommand::Clear();
	}
	

	
	{
		BENTO_PROFILE_SCOPE("Renderer Draw");
		Bento::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Bento::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.3f, 0.3f, 1.0f });
		Bento::Renderer2D::DrawQuad({ 2.0f,1.0f }, { 1.0f, 1.0f }, { 0.3f, 0.8f, 0.3f, 1.0f });
		Bento::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 100.0f, 100.0f }, m_Texture);
		Bento::Renderer2D::EndScene();
	}
	

	
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	
	ImGui::End();
}

void Sandbox2D::OnEvent(Bento::Event& e)
{
	m_CameraController.OnEvent(e);

	
}
