#include "renderer3d.hpp"
#include "config.hpp"
#include <GL/glew.h>

#include "GLFW/glfw3.h"
#include <GL/GL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "effect.hpp"
#include "texture.hpp"
#include "grid.hpp"

namespace Graphic{

	Renderer::Renderer():
		m_camera(c_cameraLocation, c_cameraOrigin, glm::radians(60.f)),
		m_renderMode(RenderModes::Simple)
	//	m_effects({ Effect("grid") })
	{
		m_effects.reserve(Effects::Count);
		m_effects.emplace_back("beam",
			BlendMode(BlendMode::BLEND_OPERATION::ADD, BlendMode::BLEND::SRC_ALPHA, BlendMode::BLEND::ONE),
			DepthState(DepthState::COMPARISON_FUNC::ALWAYS));
		m_effects.emplace_back("sun",
			BlendMode(BlendMode::BLEND_OPERATION::ADD, BlendMode::BLEND::ONE, BlendMode::BLEND::ONE),
			DepthState(DepthState::COMPARISON_FUNC::ALWAYS));
//		glEnable(GL_CULL_FACE);
	}

	// ********************************************************************* //
	void Renderer::setRenderMode(RenderModes _mode)
	{
		m_renderMode = _mode;
		if(_mode == RenderModes::WireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Renderer::addMesh(Mesh* _mesh)
	{
		m_meshes.push_back(_mesh);
		_mesh->updateNormals();
		_mesh->indexVBO();

		_mesh->GetVertices().upload();
		_mesh->GetNormals().upload();
		_mesh->GetIndices().upload();
	}

	// ********************************************************************* //
	void Renderer::draw(GLFWwindow* _window, Grid& grid, Galaxy& _galaxy)
	{
		const Effect& effect = m_effects[Effects::Beam];

		glClearColor(0.0f, 0.0f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		effect.set();

		GLuint MatrixID = glGetUniformLocation(effect.getProgId(), "MVP");
		glm::mat4 mvp = m_camera.getViewProjection();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	//	glEnable(GL_POLYGON_SMOOTH);
	/*	GLuint lightDir = glGetUniformLocation(effect.getProgId(), "ulightDirection");
		GLuint textureSamp = glGetUniformLocation(effect.getProgId(), "utextureSampler");
		GLuint textureSamp2 = glGetUniformLocation(effect.getProgId(), "utextureSampler2");*/

	//	static Texture texture("texture/grass.DDS");
	//	static Texture textureRock("texture/rock.DDS");

//		glUniform4f(lightDir, 0.4472f, 0.8944f, 0.f, 0.f);

/*		for (auto& mesh : m_meshes)
		{
			const VertexBuffer<>& vb = mesh->GetVertices();

			//set uniforms of the model
			glm::mat4 mvp = m_camera.getViewProjection() * mesh->GetModelMatrix();
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
			glUniformMatrix4fv(mmID, 1, GL_FALSE, &mesh->GetModelMatrix()[0][0]);
			uint32_t col = mesh->GetColor();
			glUniform4f(colorId, uint8_t(col >> 24) / 255.f, uint8_t(col >> 16) / 255.f, uint8_t(col >> 8) / 255.f, uint8_t(col) / 255.f);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.getId());
			// Texture Unit 0
			glUniform1i(textureSamp, 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureRock.getId());
			// Texture Unit 1
			glUniform1i(textureSamp2, 1);

			glBindBuffer(GL_ARRAY_BUFFER, vb.getId());
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glBindBuffer(GL_ARRAY_BUFFER, mesh->GetNormals().getId());
			glVertexAttribPointer(
				1,
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndices().getId());
			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				mesh->GetIndices().size(),    // count
				GL_UNSIGNED_INT,   // type
				(void*)0           // element array buffer offset
			);
			
		}*/
		// the grid
		grid.draw(effect, m_camera.getViewProjection());

		m_effects[Sun].set();

		GLuint camera = glGetUniformLocation(m_effects[Sun].getProgId(), "CAM_POS");
		MatrixID = glGetUniformLocation(m_effects[Sun].getProgId(), "MVP");

		mvp = m_camera.getViewProjection();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glm::vec4 test = mvp * glm::vec4(0.f, 0.f, 0.f, 1.f);//glm::vec4(m_camera.getPosition(), 1.f);
		test /= abs(test.w);

		glUniform3f(camera, 0.f, 0.f, 8.f);
		_galaxy.draw(m_effects[Sun]);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}