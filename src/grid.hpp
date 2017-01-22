#pragma once

#include <functional>

#include "vertexbuffer.hpp"
#include "effect.hpp"
#include "mesh.hpp"

namespace Graphic {
	class Grid
	{
	public:
		Grid(float _thickness = 5.f, float _density = 0.5f, const glm::vec4& _color = glm::vec4(1.f,1.f,1.f, 1.f));

		void preprocess(glm::vec2 _playerPos);
		glm::vec2 process(float _deltaTime);
		void draw(const Effect& _effect, const glm::mat4& _viewProjection);

		const VertexBuffer<>& getVertices() const { return m_vertexBuffer; }

		void applyFunction(std::function<glm::vec2(glm::vec2)> _function, float _deltaTime);
	private:
		std::vector<glm::vec2> m_origins;
		std::vector<glm::vec2> m_points;
		std::vector<glm::vec2> m_pointsBefore;
		std::vector<std::pair<glm::vec2,float>> m_distances;
		VertexBuffer<> m_vertexBuffer;
	};
}