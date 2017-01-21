#include "vertexbuffer.hpp"
#include "effect.hpp"
#include "mesh.hpp"

namespace Graphic {
	class Grid
	{
	public:
		Grid(float _thickness = 5.f, float _density = 5.f, const glm::vec4& _color = glm::vec4(1.f,1.f,1.f, 1.f));

		const VertexBuffer<>& getVertices() const { return m_vertexBuffer; }
	private:

		VertexBuffer<> m_vertexBuffer;
	};
}