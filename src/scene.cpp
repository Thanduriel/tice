#include "scene.hpp"
#include "globals.hpp"
#include "config.hpp"

Scene::Scene(GLFWwindow* _window)
	: m_renderer(),
	m_inputManager(*_window, m_renderer.getCamera(), m_renderer)
{
}


void Scene::process(float _dTime)
{
	m_inputManager.process(_dTime);
}

void Scene::draw(GLFWwindow* _window)
{
	m_renderer.draw(_window);
}
