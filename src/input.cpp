#include "input.hpp"
#include "globals.hpp"

#include "GLFW/glfw3.h"

using namespace glm;

namespace Input{
	InputManager::InputManager(GLFWwindow& _window, Graphic::Camera& _camera, Graphic::Renderer& _renderer, Game::Character& _player) :
		m_camera(_camera),
		m_window(_window),
		m_renderer(_renderer),
		m_player(_player)
	{}

	void InputManager::process(float _deltaTime)
	{
		double width_2 = Config::g_windowWidth / 2.0;
		double height_2 = Config::g_windowHeight / 2.0;
		double x, y;
		glfwGetCursorPos(&m_window, &x, &y);

		float dx = float(width_2 - x) / Config::g_windowWidth;
		float dy = float(height_2 - y) / Config::g_windowHeight;
		dx *= Config::g_aspectRatio;
		if (dx*dx + dy*dy < 0.01f)
		{
			dx = 0.f;
			dy = 0.f;
		} 
		glm::vec2 vel(dx, dy);
		float l = length(vel);

		m_player.setTargetVelocity(7.5f * std::min(l, 0.5f) * vel / l);

		m_camera.update(m_player.getPosition());

		//other options
		if (glfwGetKey(&m_window, GLFW_KEY_1))
			m_renderer.setRenderMode(Graphic::RenderModes::WireFrame);
		else if (glfwGetKey(&m_window, GLFW_KEY_2))
			m_renderer.setRenderMode(Graphic::RenderModes::Simple);
		else if (glfwGetKey(&m_window, GLFW_KEY_3))
			m_renderer.setRenderMode(Graphic::RenderModes::Textured);

		//reset camera
		if (glfwGetKey(&m_window, GLFW_KEY_0))
			m_camera.reset();

		// close window
		if (glfwGetKey(&m_window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(&m_window, 1);
	}
}