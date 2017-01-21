#include "grid.hpp"

namespace Graphic {
	const int c_size = 256;
	const int c_sizeSqr = c_size * c_size;

	Grid::Grid(float _thickness, float _density, const glm::vec4& _color)
//		m_effect("grid")
	{
	//	m_vertexBuffer.emplace_back(_thickness, _density, _color.w);
	//	m_vertexBuffer.emplace_back(_color.x, _color.y, _color.z);

		m_origins.resize(c_sizeSqr);
		m_points.resize(c_sizeSqr);
		for (int i = 0; i < c_sizeSqr; ++i)
		{
			int x = i % c_size;
			int y = i / c_size;

			m_origins[i] = glm::vec2(x * _density, y * _density);
			m_points[i] = m_origins[i];
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

	// ************************************************************ //
	void Grid::process(float _deltaTime)
	{
		for (int i = 0; i < c_sizeSqr; ++i)
			m_points[i] -= (m_points[i] - m_origins[i]) * _deltaTime * 0.7f;
	}
	
	// ************************************************************ //
	void Grid::draw(const Effect& _effect, const glm::mat4& _viewProjection)
	{
		GLuint MatrixID = glGetUniformLocation(_effect.getProgId(), "MVP");
		GLuint colorId = glGetUniformLocation(_effect.getProgId(), "uColor");
		GLuint thicknessId = glGetUniformLocation(_effect.getProgId(), "uThickness");

		glm::mat4 mvp = _viewProjection;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniform4f(colorId, 1.f, 1.f, 0.f, 0.5f);
		glUniform1f(thicknessId, 0.02f);

		m_vertexBuffer.clear();

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

		//glBindBuffer(GL_ARRAY_BUFFER, vb.getId());

		glDrawArrays(GL_LINES, 0, m_vertexBuffer.size());
	}

	// ************************************************************ //
	void Grid::applyFunction(std::function<glm::vec2(glm::vec2)> _function, float _deltaTime)
	{
		for (int i = 0; i < c_sizeSqr; ++i)
		{
			m_points[i] += _function(m_points[i]) * _deltaTime; // m_points
		}
	}
}