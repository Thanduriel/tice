#include <iostream>
#include <time.h>
#include <string>

#include <GL/glew.h>

#include "GLFW/glfw3.h"
#include <GL/GL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "scene.hpp"
#include "globals.hpp"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Config::g_windowWidth, Config::g_windowHeight, "World Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		return -1;
	}

	Graphic::Renderer renderer;
	std::unique_ptr<Scene> scene(new World01(window, renderer));

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	clock_t c = clock();

	bool finished = false;
	float waitTime = 0.f;
	int worldCount = 0;

	bool replayMode = true;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float frameTime = float(clock() - c) / CLOCKS_PER_SEC;
		c = clock();

	//	glfwSetWindowTitle(window, std::to_string(frameTime).c_str());
		
		if (glfwGetKey(window, GLFW_KEY_R)) replayMode = true;
		else if (glfwGetKey(window, GLFW_KEY_C)) replayMode = false;

		if (finished)
		{
			waitTime += frameTime;

			//next level
			if (waitTime > 3.f)
			{
				if(!replayMode) ++worldCount;

				switch (worldCount)
				{
				case 0: scene = std::make_unique<World01>(window, renderer); break;
				case 1: scene = std::make_unique<World02>(window, renderer); break;
				case 2: scene = std::make_unique<World03>(window, renderer); break;
				default: glfwSetWindowShouldClose(window, 1);
				}

				finished = false;
				waitTime = 0.f;
			}
		}
		else
		{
			finished = scene->process(frameTime);
			scene->draw(window);
		}
	}

	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}