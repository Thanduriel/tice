#pragma once

#include "vertexbuffer.hpp"
#include "effect.hpp"

namespace Graphic {
	class Galaxy
	{
	public:
		Galaxy();

		void draw(const Effect& _effect);
		void process(float _deltaTime);
	private:
		float m_gameTime;
		std::vector<glm::vec2> m_points;
		VertexBuffer<> m_vertexBuffer;
	};
}