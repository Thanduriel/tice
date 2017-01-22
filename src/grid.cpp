#include <algorithm>

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
		m_distances.resize(c_sizeSqr);
		m_pointsBefore.resize(c_sizeSqr);
		for (int i = 0; i < c_sizeSqr; ++i)
		{
			int x = i % c_size;
			int y = i / c_size;

			m_origins[i] = glm::vec2(x * _density, y * _density);
			m_points[i] = m_origins[i];
			m_pointsBefore[i] = m_origins[i];
		}
	}

	// ************************************************************ //
	void Grid::preprocess(glm::vec2 _playerPos)
	{
		for (int i = 0; i < c_sizeSqr; ++i)
		{
			glm::vec2 dir = _playerPos - m_points[i];
			m_distances[i].second = dir.x * dir.x + dir.y * dir.y;
		}
	}

	// ************************************************************ //
	glm::vec2 Grid::process(float _deltaTime)
	{
		for (int i = 0; i < c_sizeSqr; ++i)
		{
			m_points[i] -= (m_points[i] - m_origins[i]) * _deltaTime * 0.7f;
		}

		for (int i = 0; i < c_sizeSqr; ++i)
		{
			m_distances[i].first = m_points[i] - m_pointsBefore[i];
			m_pointsBefore[i] = m_points[i];
		}
		auto f = [] (const std::pair<glm::vec2, float>& _lhs, std::pair<glm::vec2, float> _rhs)
		{
			return _lhs.second > _rhs.second;
		};

		std::make_heap(m_distances.begin(), m_distances.end(), f);

		glm::vec2 contraction(0.f);
		for (int i = 0; i < 4; ++i)
		{
			contraction += m_distances.front().first;
			std::pop_heap(m_distances.begin(), m_distances.end()-i, f);
		}
		if (contraction.x > 0.2f)
			int brk = 42;

		return contraction * 0.25f;
	}
	
	// ************************************************************ //
	void Grid::draw(const Effect& _effect, const glm::mat4& _viewProjection)
	{
		GLuint MatrixID = glGetUniformLocation(_effect.getProgId(), "MVP");
		GLuint colorId = glGetUniformLocation(_effect.getProgId(), "uColor");
		GLuint thicknessId = glGetUniformLocation(_effect.getProgId(), "uThickness");

		glm::mat4 mvp = _viewProjection;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniform4f(colorId, 0.f, 1.f, 0.f, 0.5f);
		glUniform1f(thicknessId, 0.02f);

		m_vertexBuffer.clear();
		m_vertexBuffer.reserve(c_sizeSqr);

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
			m_points[i] += _function(m_origins[i]) * _deltaTime; // m_points
		}
	}
}