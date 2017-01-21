#include "vertexbuffer.hpp"
#include "effect.hpp"
#include "mesh.hpp"

namespace Graphic {
	class Grid
	{
	public:
		Grid(float _thickness = 5.f, float _density = 5.f, const glm::vec4& _color = glm::vec4(1.f,1.f,1.f, 1.f));

		void draw();

		const VertexBuffer<>& getVertices() const { return m_vertexBuffer; }
	private:
		std::vector<glm::vec2> m_points;
		VertexBuffer<> m_vertexBuffer;
	};
}