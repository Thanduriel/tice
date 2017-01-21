#pragma once

#include <glm.hpp>

namespace Graphic{

	class Camera
	{
	public:
		Camera(glm::vec3 _position, glm::vec3 _origin, float _fov);

		const glm::mat4& getViewProjection() const { return m_viewProjectionMatrix; }
		const glm::mat4& getView() const { return m_viewMatrix; }
		const glm::mat4& getProjection() const { return m_projectionMatrix; }

		const glm::vec3& getPosition() const { return m_position; }

		void update(glm::vec2 _pos);

		// Sets back this camera to the initial state.
		void reset();
	private:
		void updateMatrix();

		float m_rotateX, m_rotateY;
		glm::vec3 m_position, m_direction;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		glm::mat4 m_viewProjectionMatrix;

		//inital state
		glm::vec3 m_initialPosition;
		glm::vec3 m_initialOrigin;
	};

}