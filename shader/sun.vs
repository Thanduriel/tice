#version 330 core

layout(location = 0) in vec3 position;

out vec4 vs_position;

uniform mat4 MVP;

void main()
{
	vs_position = MVP * vec4(position, 1);
}
