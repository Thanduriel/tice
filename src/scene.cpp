#include "scene.hpp"
#include "globals.hpp"
#include "config.hpp"

Scene::Scene(GLFWwindow* _window)
	: m_renderer(),
	m_player(),
	m_inputManager(*_window, m_renderer.getCamera(), m_renderer, m_player),
	m_grid(0.01f, 2.f)
{
}


void Scene::process(float _dTime)
{
	m_inputManager.process(_dTime);
	m_player.process(_dTime);
	m_grid.process(_dTime);
	m_galaxy.process(_dTime);
}

void Scene::draw(GLFWwindow* _window)
{
	m_renderer.draw(_window, m_grid, m_galaxy);
}
