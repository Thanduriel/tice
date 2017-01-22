#pragma once

#include "glm.hpp"
#include "particlesystem.hpp"

namespace Game {

	class Goal
	{
	public:
		Goal(glm::vec2 _position, float _size) :
			m_position(_position),
			m_size(_size)
		{
		}

		// takes playerposition
		// returns true when the player has reached the goal
		bool process(float _deltaTime, glm::vec2 _position);
	private:
		glm::vec2 m_position;
		float m_size;
	};
}