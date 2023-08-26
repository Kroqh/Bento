#include "Bentopch.h"
#include "OrthographicCameraController.h"

#include "Bento/Core/Input.h"
#include "Bento/Core/KeyCodes.h"

namespace Bento {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		BENTO_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraSpeed * ts;

		if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraSpeed * ts;

		if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		if (m_Rotation) {

			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraTurnRate * ts;

			if (Input::IsKeyPressed(Bento::Key::Q))
				m_CameraRotation += m_CameraTurnRate * ts;

		}

		

		m_Camera.SetPositon(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		BENTO_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BENTO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BENTO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		BENTO_PROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset() * 0.25f;

		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		BENTO_PROFILE_FUNCTION();
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		CalculateView();
	}

}