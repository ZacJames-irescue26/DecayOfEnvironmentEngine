#pragma once

#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Core/Timestep.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"


namespace DOE_Engine
{
	class OrthographicCameraController
	{
	public:

		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		float GetZoomLevel() const { return m_zoomLevel; }
		void SetZoomLevel(float level) { m_zoomLevel = level; }
	private:

		bool OnMouseScrolled(DOE_Engine::MouseScrolledEvent& e);
		bool OnWindowResized(DOE_Engine::WindowResizeEvent& e);

		float m_AspectRatio;
		float m_zoomLevel = 1.0f;
		OrthographicCamera m_Camera;


		glm::vec3 m_CameraPosition = {0.0, 0.0, 0.0};
		float m_CameraSpeed = 1.0f;
	};
}