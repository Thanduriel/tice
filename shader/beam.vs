#version 330 core

layout(location = 0) in vec3 position;

out vec4 vs_position;
out float thickness;
out float density;
out vec4 vs_color;

uniform mat4 MVP;

void main()
{
	vs_position = MVP * vec4(position, 1);
	thickness = 0.0001;
	density = 1;
}
