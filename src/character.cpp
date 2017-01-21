#include "character.hpp"

namespace Game {

	const float c_acceleration = 0.1f;

	Character::Character():
		m_targetVelocity(0.f)
	{

	}

	void Character::process(float _deltaTime)
	{
		glm::vec2 dir = m_targetVelocity- m_velocity;
		float l = length(dir);
		if(l > 0.1f) m_velocity += glm::normalize(dir) * c_acceleration;

		Body::process(_deltaTime);
	}
}