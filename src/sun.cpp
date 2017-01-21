#include "sun.hpp"
#include "globals.hpp"

namespace Graphic {
	Galaxy::Galaxy():
		m_gameTime(0.f)
	{
		m_points.emplace_back(1.f, 1.f);
	}

	void Galaxy::process(float _deltaTime)
	{
		m_gameTime += _deltaTime;
	}

	void Galaxy::draw(const Effect& _effect)
	{
		m_vertexBuffer.clear();
		for (auto& s : m_points)
			m_vertexBuffer.emplace_back(project(s));

		m_vertexBuffer.upload();

		GLuint resolution = glGetUniformLocation(_effect.getProgId(), "iResolution");
		GLuint time = glGetUniformLocation(_effect.getProgId(), "iGlobalTime");

		glUniform2f(resolution, (float)Config::g_windowWidth, (float)Config::g_windowHeight);
		glUniform1f(time, m_gameTime);

		glDrawArrays(GL_POINTS, 0, m_vertexBuffer.size());
	}
}