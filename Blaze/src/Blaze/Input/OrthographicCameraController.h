#pragma once

#include "Blaze/Core/Timestep.h"

#include "Blaze/Event/ApplicationEvent.h"
#include "Blaze/Event/MouseEvent.h"

#include "Blaze/Renderer/OrthographicCamera.h"

namespace Blaze
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(const float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(const MouseScrolledEvent& event);
		bool OnWindowResized(const WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 3.0f, m_CameraRotationSpeed = 180.0f;
	};
}
