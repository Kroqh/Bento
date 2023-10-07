#pragma once
#include <Bento.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

namespace Bento {

	class EditorLayer : public Bento::Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDeAttach() override;
		virtual void OnUpdate(Bento::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnOverlayRender() override;
		virtual void OnEvent(Bento::Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);

		void SaveSceneAs();
		void SaveScene();
		bool PickEntity(MouseButtonReleasedEvent& e);
		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();


		// UI Panels
		void UI_ToolBar();

	private:
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		bool m_DrawOverlay;

		Bento::OrthographicCameraController m_CameraController;

		Bento::Ref<Bento::Texture2D> m_Texture;
		Bento::Ref<Bento::Texture2D> m_PlayIcon;
		Bento::Ref<Bento::Texture2D> m_PauseIcon;

		Bento::Ref<Bento::Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;

		Entity m_SquareEntity;

		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		enum  class SceneState
		{
			Edit = 0, Play = 1
		};

		SceneState m_SceneState = SceneState::Edit;
	};

}



