#include "scene.hpp"
#include "globals.hpp"
#include "config.hpp"
#include "function.hpp"

Scene::Scene(GLFWwindow* _window)
	: m_renderer(),
	m_player(),
	m_inputManager(*_window, m_renderer.getCamera(), m_renderer, m_player),
	m_grid(0.01f, 0.5f),
	m_gameTime(0.f)
{
}


void Scene::process(float _dTime)
{
	m_gameTime += _dTime;

	if (m_gameTime > 1.f && m_gameTime < 30.5f)
	{
		static Physics::CrazyWave wave; wave.setOrigin(glm::vec2(20.1f, 20.1f));
		wave.setShift(m_gameTime);
		m_grid.applyFunction(wave, _dTime);
	}
	m_inputManager.process(_dTime);
	m_player.process(_dTime);
	m_grid.process(_dTime);
	m_galaxy.process(_dTime);
}

void Scene::draw(GLFWwindow* _window)
{
	m_renderer.draw(_window, m_grid, m_galaxy);
}
