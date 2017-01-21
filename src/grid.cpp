#include "grid.hpp"

namespace Graphic {
	const int c_size = 64;

	Grid::Grid(float _thickness, float _density, const glm::vec4& _color)
//		m_effect("grid")
	{
	//	m_vertexBuffer.emplace_back(_thickness, _density, _color.w);
	//	m_vertexBuffer.emplace_back(_color.x, _color.y, _color.z);

		m_points.resize(c_size * c_size);
		for (int i = 0; i < c_size * c_size; ++i)
		{
			int x = i % c_size;
			int y = i / c_size;

			m_points[i] = glm::vec2(x * _density, y * _density);
		}

/*		for(int ix = 0; ix < 50; ++ix)
			for (int iy = 0; iy < 50; ++iy)
			{
				m_vertexBuffer.emplace_back(iy -1.f, 0.f, ix * 1.f);
				m_vertexBuffer.emplace_back(iy + 1.f, 0.f, ix * 1.f);
			}*/

/*		for (int i = -50; i < 50; ++i)
		{
			m_vertexBuffer.emplace_back(100.f, 0.f, i * 1.f);
			m_vertexBuffer.emplace_back(-100.f, 0.f, i * 1.f);
		}

		for (int i = -50; i < 50; ++i)
		{
			m_vertexBuffer.emplace_back(i * 1.f, 0.f, 100.f);
			m_vertexBuffer.emplace_back(i * 1.f , 0.f,- 100.f);
		}
		*/
	}
	
	void Grid::draw()
	{
		m_vertexBuffer.reserve(m_points.size());

		for (int i = 0; i < c_size * c_size - c_size; ++i)
		{
			int x = i % c_size;
			int y = i / c_size;

			if (x != c_size - 1)
			{
				m_vertexBuffer.emplace_back(project(m_points[i]));
				m_vertexBuffer.emplace_back(project(m_points[i + 1]));
			}
			m_vertexBuffer.emplace_back(project(m_points[i]));
			m_vertexBuffer.emplace_back(project(m_points[i + c_size]));
		}

		m_vertexBuffer.upload();
	}
}