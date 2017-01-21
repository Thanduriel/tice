#pragma once

#include <array>

#include "mesh.hpp"
#include "camera.hpp"
#include "effect.hpp"

namespace Graphic{

	class Renderer
	{
	public:
		Renderer();

		void draw(GLFWwindow* _window);

		void addMesh(Mesh* _mesh);

		Camera& getCamera() { return m_camera; }

		void setRenderMode(RenderModes _mode);
	private:
		RenderModes m_renderMode;
		Camera m_camera;

		std::vector<Mesh*> m_meshes;
	//	std::array< Effect, 1 > m_effects;
	};
}