#pragma once

#include "glm.hpp"

namespace Physics {

	class Body
	{
	public:
		Body() : m_position(0.f), m_velocity(0.f) {}

		void setPosition(glm::vec2 _position) { m_position = _position; }
		glm::vec2 getPosition() const { return m_position; }

		void process(float _deltaTime) { m_position += _deltaTime * m_velocity; }

		void setVelocity(glm::vec2 _vel) { m_velocity = _vel; }
		glm::vec2 getVelocity() const { return m_velocity; }
	protected:
		glm::vec2 m_position;
		glm::vec2 m_velocity;
	};

}