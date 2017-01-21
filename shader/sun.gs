#version 330

#define OUT_VERTS 4

in vec4 vs_position[1];
out vec3 SUN_CENTER;

layout(points) in;
layout(triangle_strip, max_vertices = OUT_VERTS) out;

uniform vec2 iResolution;
uniform mat4 MVP;
void main()
{
	SUN_CENTER =vs_position[0].xyz / abs(vs_position[0].w);
	
//	SUN_CENTER.x *= iResolution.y / iResolution.x;
	/*gl_Position = vec4(-1.f, -1.f, 0.f, 1.f);
	EmitVertex();
	gl_Position = vec4(1.f, -1.f, 0.f, 1.f);
	EmitVertex();
	gl_Position = vec4(-1.f, 1.f, 0.f, 1.f);
	EmitVertex();
	gl_Position = vec4(1.f, 1.f, 0.f, 1.f);
	EmitVertex();
	EndPrimitive();*/
	gl_Position = vs_position[0] + vec4(-1.5f, -1.5f, 0.f, 0.f);
	EmitVertex();
	gl_Position = vs_position[0] + vec4(1.5f, -1.5f, 0.f, 0.f);
	EmitVertex();
	gl_Position = vs_position[0] + vec4(-1.5f, 1.5f, 0.f, 0.f);
	EmitVertex();
	gl_Position = vs_position[0] + vec4(1.5f, 1.5f, 0.f, 0.f);
	EmitVertex();
	EndPrimitive();
}