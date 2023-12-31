﻿#include "blzpch.h"
#include "OrthographicCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Blaze
{
	OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
	{
		SetProjection(left, right, bottom, top);
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProjection(const float left, const float right, const float bottom, const float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		RecalculateViewMatrix();
	}


	void OrthographicCamera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
