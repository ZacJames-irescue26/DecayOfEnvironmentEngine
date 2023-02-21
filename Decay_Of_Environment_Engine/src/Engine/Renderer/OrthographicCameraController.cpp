#include "pch.h"
#include "OrthographicCameraController.h"


namespace DOE_Engine
{


	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_zoomLevel, m_AspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(DOE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(DOE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.GetYOffset();
		m_zoomLevel = std::max(m_zoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_zoomLevel, m_AspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_zoomLevel, m_AspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

		return false;
	}

}