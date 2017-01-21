#pragma once

#include "camera.hpp"
#include "renderer3d.hpp"
#include "GLFW/glfw3.h"
#include "character.hpp"

namespace Input{
	class InputManager
	{
	public:
		InputManager(GLFWwindow& _window, Graphic::Camera& _camera, Graphic::Renderer& _renderer, Game::Character& _player);

		void process(float _deltaTime);

	private:
		GLFWwindow& m_window;
		Graphic::Camera& m_camera;
		Graphic::Renderer& m_renderer;
		Game::Character& m_player;
	};
}