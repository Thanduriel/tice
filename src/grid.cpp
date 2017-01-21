#include "grid.hpp"

namespace Graphic {
	Grid::Grid(float _thickness, float _density, const glm::vec4& _color)
//		m_effect("grid")
	{
	//	m_vertexBuffer.emplace_back(_thickness, _density, _color.w);
	//	m_vertexBuffer.emplace_back(_color.x, _color.y, _color.z);

		for (int i = -50; i < 50; ++i)
		{
			m_vertexBuffer.emplace_back(100.f, 0.f, i * 1.f);
			m_vertexBuffer.emplace_back(-100.f, 0.f, i * 1.f);
		}

		for (int i = -50; i < 50; ++i)
		{
			m_vertexBuffer.emplace_back(i * 1.f, 0.f, 100.f);
			m_vertexBuffer.emplace_back(i * 1.f , 0.f,- 100.f);
		}

		m_vertexBuffer.upload();
	}
}