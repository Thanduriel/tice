#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "glm.hpp"
#include "vertexbuffer.hpp"

namespace Graphic {

	struct Particle
	{
		Particle(const glm::vec3& _position, const glm::vec3& _velocity, float _time) :
			position(_position),
			velocity(_velocity),
			lifeTime(_time) {}
		glm::vec3 position;
		glm::vec3 velocity;
		float lifeTime;
	};

	class ParticleSystem
	{
	public:
		void build(const glm::vec3& _position, const glm::vec3& _velocity, float _time);

		void process(float _deltaTime);

		void draw();
	private:
		float m_gameTime;

		std::vector<Particle> m_particles;
		VertexBuffer<> m_vertexBuffer;
	};

	//is constructed in Renderer::Renderer
	extern std::unique_ptr<ParticleSystem> g_particleSystem;
}