#include "character.hpp"
#include "particlesystem.hpp"

namespace Game {

	const float c_acceleration = 0.1f;

	Character::Character(glm::vec2 _position):
		m_targetVelocity(0.f)
	{
		setPosition(_position);
	}

	void Character::process(float _deltaTime)
	{
		glm::vec2 dir = m_targetVelocity- m_velocity;
		float l = length(dir);
		if(l > 0.1f) m_velocity += glm::normalize(dir) * c_acceleration;
		Graphic::g_particleSystem->build(Graphic::project(m_position), glm::vec3(0.f), 1.f);

		Body::process(_deltaTime);
	}
}