#pragma once

#include "renderer3d.hpp"
#include "input.hpp"
#include "grid.hpp"
#include "character.hpp"
#include "sun.hpp"

class Scene
{
public:
	Scene(GLFWwindow* _window);

	void process(float _dTime);
	void draw(GLFWwindow* _window);

protected:
	Graphic::Renderer m_renderer;
private:
	Input::InputManager m_inputManager;
	Graphic::Grid m_grid;
	Game::Character m_player;
	Graphic::Galaxy m_galaxy;
};