#include "Sandbox2D.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;
static const uint32_t s_MapHeight = 12;
static const char* s_MapTiles =

"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWDDDDDDWWWWWWWWWWWW"
"WWWWDDDDDDDDDDDWWWWWWWWW"
"WWWDDDDDDDDDDDDDDDWWWWWW"
"WWDDDDDDDDDDDDDDDDDWWWWW"
"WDDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDWWWWW"
"WWWWWDDDDDDWWDDDDDWWWWWW"
"WWWWWWWWDDDWWDDDDWWWWWWW"
"WWWWWWWWWDDDDDDDWWWWWWWW"
"WWWWWWWWWWDDDDWWWWWWWWWW";


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{
	
}

void Sandbox2D::OnAttach()
{
	BENTO_PROFILE_FUNCTION();
	m_Texture = Bento::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Bento::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	s_TextureMap['D'] = Bento::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = Bento::SubTexture2D::CreateFromCoords(m_SpriteSheet, {11, 11}, {128, 128});
	m_ErrorTexture = Bento::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 6 }, { 128, 128 });
	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
	
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
	// Reset stats
	Bento::Renderer2D::ResetStats();
	{
		BENTO_PROFILE_SCOPE("Renderer prep");
		Bento::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Bento::RenderCommand::Clear();
	}
	

	
	{
		static float rotation = 0.0f;

		rotation += ts * 50.0f;

		BENTO_PROFILE_SCOPE("Renderer Draw");
		Bento::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (uint32_t y = 0; y < s_MapHeight; y++)
		{
			for (uint32_t x = 0; x < s_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * s_MapWidth];
				Bento::Ref<Bento::SubTexture2D> texture;
				if (s_TextureMap.find(tileType) != s_TextureMap.end())
					texture = s_TextureMap[tileType];
				else
					texture = m_ErrorTexture;

			}
		}
		Bento::Renderer2D::EndScene();

	}
	if (Bento::Input::IsMouseButtonPressed(Bento::Mouse::Button0))
		{
			glm::vec2 mousePos = Bento::Input::GetMousePosition();
			auto width = Bento::Application::Get().GetWindow().GetWidth();
			auto height = Bento::Application::Get().GetWindow().GetHeight();
			
			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			mousePos.x = (mousePos.x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			mousePos.y = bounds.GetHeight() * 0.5f - (mousePos.y / height) * bounds.GetHeight();
			m_Particle.Position = { mousePos.x + pos.x, mousePos.y + pos.y };
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	
}

void Sandbox2D::OnImGuiRender()
{
	

		ImGui::Begin("Settings");
		auto stats = Bento::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		ImGui::Text("Particle Settings");
		ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
		ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
}

void Sandbox2D::OnEvent(Bento::Event& e)
{
	m_CameraController.OnEvent(e);

	
}
