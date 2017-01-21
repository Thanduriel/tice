#pragma once

#include <array>

#include "mesh.hpp"
#include "camera.hpp"
#include "effect.hpp"
#include "grid.hpp"
#include "sun.hpp"

namespace Graphic{

	class Renderer
	{
	public:
		enum Effects{
			Beam,
			Sun,
			BlackHole,
			Count
		};

		Renderer();

		void draw(GLFWwindow* _window, Grid& _grid, Galaxy& _galaxy);

		void addMesh(Mesh* _mesh);

		Camera& getCamera() { return m_camera; }

		void setRenderMode(RenderModes _mode);
	private:
		RenderModes m_renderMode;
		Camera m_camera;

		std::vector<Mesh*> m_meshes;
		std::vector< Effect > m_effects;
	//	std::array< Effect, 1 > m_effects;
	};
}