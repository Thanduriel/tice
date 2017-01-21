#pragma once

#include "glm.hpp"

namespace Physics {

	class Body
	{
	public:
		glm::vec2 getPosition() const { return m_position; }

		void process(float _deltaTime) { m_position += _deltaTime * m_velocity; }

		void setVelocity(glm::vec2 _vel) { m_velocity = _vel; }
		glm::vec2 getVelocity() const { return m_velocity; }
	private:
		glm::vec2 m_position;
		glm::vec2 m_velocity;
	};

}