#include "goal.hpp"
#include "random.hpp"

namespace Game {

	bool Goal::process(float _deltaTime, glm::vec2 _position)
	{
		static Util::Random rng(2472457);
		glm::vec3 dir(rng.uniform(-1.f, 1.f), rng.uniform(-1.f, 1.f), rng.uniform(-1.f, 1.f));
		Graphic::g_particleSystem->build(Graphic::project(m_position), glm::normalize(dir), m_size);

		return glm::distance(_position, m_position) < m_size;
	}
}