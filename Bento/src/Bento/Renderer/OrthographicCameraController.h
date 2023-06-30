#pragma once
#include "Bento/Renderer/OrthographicCamera.h"
#include "Bento/Core/Timestep.h"

#include "Bento/Events/ApplicationEvent.h"
#include "Bento/Events/MouseEvent.h"
namespace Bento {

	class OrthographicCameraController {

	public:
		OrthographicCameraController(float aspectRatio, bool rotation); //  aspectratio * 2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 1.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraTurnRate = 25.0f;

	};

}