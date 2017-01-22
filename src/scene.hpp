#pragma once

#include "renderer.hpp"
#include "input.hpp"
#include "grid.hpp"
#include "character.hpp"
#include "sun.hpp"
#include "goal.hpp"

class Scene
{
public:
	Scene(GLFWwindow* _window, Graphic::Renderer& _renderer, const Game::Goal& _goal);

	//returns true when the level has been completed
	virtual bool process(float _dTime);
	void draw(GLFWwindow* _window);

protected:
	Graphic::Renderer& m_renderer;
	float m_gameTime;

	Input::InputManager m_inputManager;
	Graphic::Grid m_grid;
	Game::Character m_player;
	Graphic::Galaxy m_galaxy;
	Game::Goal m_goal;
};

// ********************************************** //
class World01 : public Scene 
{
public:
	World01(GLFWwindow* _window, Graphic::Renderer& _renderer);
	bool process(float _deltaTime);
};

// ********************************************** //
class World02 : public Scene
{
public:
	World02(GLFWwindow* _window, Graphic::Renderer& _renderer);
	bool process(float _deltaTime);
};

// ********************************************** //
class World03 : public Scene
{
public:
	World03(GLFWwindow* _window, Graphic::Renderer& _renderer);
	bool process(float _deltaTime);
};