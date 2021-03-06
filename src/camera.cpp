#include "camera.hpp"
#include <gtc/matrix_transform.hpp>
#include "config.hpp"

using namespace glm;

namespace Graphic{
	Camera::Camera(glm::vec3 _position, glm::vec3 _origin, float _fov)
		: m_viewMatrix(glm::lookAt(_position, _origin, vec3(0.f, 1.f, 0.f))),
		m_projectionMatrix(glm::perspective(glm::radians(90.0f), 16.f / 9.f, 0.1f, 100.0f)),
		m_rotateX(0.f),
		m_rotateY(0.f),
		m_position(_position),
		m_initialPosition(_position),
		m_initialOrigin(_origin)
	{
		updateMatrix();
	}

	void Camera::update(glm::vec2 _pos)
	{
		glm::vec3 direction(0.f, -1.f, 0.f);
		m_position = glm::vec3(_pos.x, m_position.y, _pos.y);

		glm::vec3 up(0.f, 0.f, 1.f);

		m_viewMatrix = glm::lookAt(m_position, m_position + direction, up);

		updateMatrix();
	}


	void Camera::reset()
	{
		m_position = m_initialPosition;
		m_direction = m_initialOrigin - m_initialPosition;
	}

	void Camera::updateMatrix()
	{
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
}