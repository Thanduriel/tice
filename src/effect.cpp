#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "effect.hpp"

using namespace std;

namespace Graphic{

	Effect::Effect(const char * _name, BlendMode _blendMode, DepthState _depthState):
		m_blendMode(_blendMode),
		m_depthState(_depthState)
	{

		string vertexPath = string("shader/") + _name + string(".vs");
		string fragPath = string("shader/") + _name + string(".ps");
		string geometryPath = string("shader/") + _name + string(".gs");

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertexPath, std::ios::in);
		if (VertexShaderStream.is_open()){
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else{
			cout << "Could not open: " << vertexPath << endl;
			getchar();
			return;
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragPath, std::ios::in);
		if (FragmentShaderStream.is_open()){
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		// Read geometry shader
		string GeometryShaderCode;
		ifstream GeomtryShaderStream(geometryPath, std::ios::in);
		if (GeomtryShaderStream.is_open()) {
			std::string Line = "";
			while (getline(GeomtryShaderStream, Line))
				GeometryShaderCode += "\n" + Line;
			GeomtryShaderStream.close();
		}
		else {
			cout << "Could not open: " << geometryPath << endl;
			getchar();
			return;
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;


		// Compile Vertex Shader
		cout << "Compiling shader : " << vertexPath << endl;
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}



		// Compile Fragment Shader
		cout << "Compiling shader : " << fragPath << endl;
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		cout << "Compiling shader : " << geometryPath << endl;
		char const * GeometrySourcePointer = GeometryShaderCode.c_str();
		glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
		glCompileShader(GeometryShaderID);

		// Check Geometry Shader
		glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
			printf("%s\n", &GeometryShaderErrorMessage[0]);
		}



		// Link the program
		printf("Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, GeometryShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}


		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);
		glDetachShader(ProgramID, GeometryShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
		glDeleteShader(GeometryShaderID);

		m_id = ProgramID;
		return;
	}


	Effect::~Effect()
	{
		glDeleteProgram(m_id);
	}

	// ****************************************************************** //
	void Effect::set() const
	{
		glUseProgram(m_id);
		m_blendMode.set();
		m_depthState.set();

		glEnableVertexAttribArray(0);
	}


	// ****************************************************************** //
	void DepthState::set() const
	{
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc((unsigned)m_function);
	}

	// ****************************************************************** //
	void BlendMode::set() const
	{
		glEnable(GL_BLEND);
		glBlendEquation(unsigned(m_equation));
		glBlendFunc(unsigned(m_opSrc), unsigned(m_opDst));
	}
}