#version 330


layout(location=0) in vec3 in_Position;

out vec4 vs_out_Position;

uniform mat4 MVP;

void main()
{
	// Pass through everything
	vs_out_Position = MVP * vec4(in_Position, 1);
}
