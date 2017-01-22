#include <iostream>

#include "scene.hpp"
#include "globals.hpp"
#include "config.hpp"
#include "function.hpp"
#include "particlesystem.hpp"

using namespace glm;
using namespace Game;

Scene::Scene(GLFWwindow* _window, Graphic::Renderer& _renderer, const Game::Goal& _goal)
	: m_renderer(_renderer),
	m_player(glm::vec2(50.f, 20.f)),
	m_inputManager(*_window, m_renderer.getCamera(), m_renderer, m_player),
	m_grid(0.01f, 0.5f),
	m_gameTime(0.f),
	m_goal(_goal)
{
}


bool Scene::process(float _dTime)
{
	m_gameTime += _dTime;

	Graphic::g_particleSystem->process(_dTime);
	m_player.process(_dTime);
	m_grid.preprocess(m_player.getPosition());
	
	m_inputManager.process(_dTime);
	glm::vec2 pos = m_grid.process(_dTime);
	m_player.setPosition(m_player.getPosition() + pos);
	m_galaxy.process(_dTime);

	bool finished = m_goal.process(_dTime, m_player.getPosition());

	if (finished)
		std::cout << "Finished level in: " << m_gameTime << std::endl;
	return finished;
}

void Scene::draw(GLFWwindow* _window)
{
	m_renderer.draw(_window, m_grid, m_galaxy);
}

// **************************************************************************** //

World01::World01(GLFWwindow* _window, Graphic::Renderer& _renderer) :
	Scene(_window, _renderer, Goal(glm::vec2(40.f, 60.f), 2.f))
{

}

bool World01::process(float _deltaTime)
{
	if (m_gameTime > 1.f && m_gameTime < 30.5f)
	{
		static Physics::SingleWave wave; wave.setOrigin(glm::vec2(50.1f, 50.1f));
		wave.setShift(m_gameTime);
		m_grid.applyFunction(wave, _deltaTime);
	}
	return Scene::process(_deltaTime);
}

// **************************************************************************** //

World02::World02(GLFWwindow* _window, Graphic::Renderer& _renderer) :
	Scene(_window, _renderer, Goal(glm::vec2(40.f, 60.f), 2.f))
{

}

bool World02::process(float _deltaTime)
{
	static Physics::SinusWave wave; wave.setOrigin(glm::vec2(80.1f, 50.1f));
	wave.setShift(m_gameTime);
	m_grid.applyFunction(wave, _deltaTime);

	return Scene::process(_deltaTime);
}

// **************************************************************************** //

World03::World03(GLFWwindow* _window, Graphic::Renderer& _renderer) :
	Scene(_window, _renderer, Goal(glm::vec2(40.f, 60.f), 2.f))
{

}

bool World03::process(float _deltaTime)
{
	static Physics::WavePack<Physics::SingleWave, Physics::SingleWave> w; 
	w.wave1.setOrigin(glm::vec2(50.1f, 50.1f));
	w.wave2.setOrigin(glm::vec2(30.1f, 45.1f));
	w.setShift(m_gameTime* 1.2f);
	m_grid.applyFunction(w, _deltaTime);
	if (m_gameTime > 4.5f)
	{
		w.setShift(m_gameTime * 1.4f - 4.5f);
		m_grid.applyFunction(w, _deltaTime);
	}
	return Scene::process(_deltaTime);
}