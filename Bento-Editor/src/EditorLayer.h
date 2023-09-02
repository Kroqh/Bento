#pragma once
#include <Bento.h>
#include "Panels/SceneHierarchyPanel.h"

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
		virtual void OnEvent(Bento::Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		bool PickEntity(MouseButtonReleasedEvent& e);

	private:
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		Bento::OrthographicCameraController m_CameraController;

		Bento::Ref<Bento::Texture2D> m_Texture;
		Bento::Ref<Bento::Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;

		EditorCamera m_EditorCamera;

		int m_frameBufferID = 0;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;

	};

}



