#include "particlesystem.hpp"

namespace Graphic {
	std::unique_ptr<ParticleSystem> g_particleSystem;

	void ParticleSystem::build(const glm::vec3& _position, const glm::vec3& _velocity, float _time)
	{
		m_particles.emplace_back(_position, _velocity, m_gameTime + _time);
	}

	void ParticleSystem::process(float _deltaTime)
	{
		m_gameTime += _deltaTime;

		auto it = std::remove_if(m_particles.begin(), m_particles.end(), [=](const Particle& _p)
		{
			return _p.lifeTime <= m_gameTime;
		});
		m_particles.erase(it, m_particles.end());

		for (auto& p : m_particles)
		{
			p.position += p.velocity * _deltaTime;
		}
	}

	void ParticleSystem::draw()
	{
		m_vertexBuffer.clear();
		for (auto& p : m_particles)
			m_vertexBuffer.push_back(p.position);

		m_vertexBuffer.upload();
		glDrawArrays(GL_POINTS, 0, m_vertexBuffer.size());
	}
}