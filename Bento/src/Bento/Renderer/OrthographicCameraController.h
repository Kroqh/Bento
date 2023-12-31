#pragma once
#include "Bento/Renderer/OrthographicCamera.h"
#include "Bento/Core/Timestep.h"

#include "Bento/Events/ApplicationEvent.h"
#include "Bento/Events/MouseEvent.h"
namespace Bento {

	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController {

	public:
		OrthographicCameraController(float aspectRatio, bool rotation); //  aspectratio * 2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; CalculateView(); }
		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

	private:

		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 1.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraTurnRate = 25.0f;

	};

}