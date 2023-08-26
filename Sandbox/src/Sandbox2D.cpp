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

	Bento::FramebufferSpecification fbSpec;
	fbSpec.Width = Bento::Application::Get().GetWindow().GetWidth();
	fbSpec.Height = Bento::Application::Get().GetWindow().GetHeight();
	m_Framebuffer = Bento::Framebuffer::Create(fbSpec);
	
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
		m_Framebuffer->Bind();
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

				Bento::Renderer2D::DrawQuad({ x - s_MapWidth / 2.0f, y - s_MapHeight / 2.0f}, {1.0f, 1.0f}, texture, 1.0f);
			}
		}
		Bento::Renderer2D::EndScene();
		m_Framebuffer->UnBind();

	}
	if (Bento::Input::IsMouseButtonPressed(Bento::Mouse::Button0))
		{
			auto [x, y] = Bento::Input::GetMousePosition();
			auto width = Bento::Application::Get().GetWindow().GetWidth();
			auto height = Bento::Application::Get().GetWindow().GetHeight();
			
			auto bounds = m_CameraController.GetBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	
}

void Sandbox2D::OnImGuiRender()
{
	static bool dockingEnabled = true;

	if (dockingEnabled) {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("Exit"))
					Bento::Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

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

		
		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2(1280.0f, 720.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		ImGui::End();

		ImGui::End();
	}

	
}

void Sandbox2D::OnEvent(Bento::Event& e)
{
	m_CameraController.OnEvent(e);

	
}
