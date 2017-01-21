#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <GL/GL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Graphic{

	inline glm::vec3 project(glm::vec2 _vec)
	{
		return glm::vec3(_vec.x, 0.f, _vec.y);
	}

	template<typename _T = glm::vec3, unsigned int _ArrayType = GL_ARRAY_BUFFER>
	class VertexBuffer : public std::vector<_T>
	{
		typedef std::vector<_T> ST;
	public:
		VertexBuffer() : m_isDirty(true)
		{
			glGenBuffers(1, &m_id);
			glBindBuffer(_ArrayType, m_id);
		}
		~VertexBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		bool isDirty() const { return m_isDirty; }

		int getId() const { return m_id; }

		void upload() const
		{
			glBindBuffer(_ArrayType, m_id);
			// Give our vertices to OpenGL.
			glBufferData(_ArrayType, ST::size() * sizeof(_T), &*ST::begin(), GL_DYNAMIC_DRAW);

			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
		}
	private:
		bool m_isDirty;

		GLuint m_id;
	};
}