#include "EditorLayer.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

namespace Bento {

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


	EditorLayer::EditorLayer()
		: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
	{

	}

	void EditorLayer::OnAttach()
	{
		BENTO_PROFILE_FUNCTION();
		m_Texture = Texture2D::Create("assets/textures/Checkerboard.png");
		m_SpriteSheet = Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
		s_TextureMap['D'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
		s_TextureMap['W'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });
		m_ErrorTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 6 }, { 128, 128 });

		m_CameraController.SetZoomLevel(5.0f);

		FramebufferSpecification fbSpec;
		fbSpec.Width = Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Framebuffer::Create(fbSpec);

	}

	void EditorLayer::OnDeAttach()
	{
		BENTO_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		BENTO_PROFILE_FUNCTION();



		// Update
		{
			BENTO_PROFILE_SCOPE("OrthographicCameraController::OnUpdate");
			m_CameraController.OnUpdate(ts);
		}


		// Render
		// Reset stats
		Renderer2D::ResetStats();
		{
			BENTO_PROFILE_SCOPE("Renderer prep");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}



		{
			static float rotation = 0.0f;

			rotation += ts * 50.0f;

			BENTO_PROFILE_SCOPE("Renderer Draw");
			Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (uint32_t y = 0; y < s_MapHeight; y++)
			{
				for (uint32_t x = 0; x < s_MapWidth; x++)
				{
					char tileType = s_MapTiles[x + y * s_MapWidth];
					Ref<SubTexture2D> texture;
					if (s_TextureMap.find(tileType) != s_TextureMap.end())
						texture = s_TextureMap[tileType];
					else
						texture = m_ErrorTexture;

					Renderer2D::DrawQuad({ x - s_MapWidth / 2.0f, y - s_MapHeight / 2.0f }, { 1.0f, 1.0f }, texture, 1.0f);
				}
			}
			Renderer2D::EndScene();
			m_Framebuffer->UnBind();

		}



	}

	void EditorLayer::OnImGuiRender()
	{
		
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
					Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {

			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

			m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
		}

		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End();


	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);


	}

}


