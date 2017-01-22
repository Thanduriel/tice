#version 330

in vec4 vs_out_Position[1];

out vec2 gs_texCoord;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform float uAspectRatio;

void main(void)
{
	vec4 position = vs_out_Position[0];
//	position.xyz /= abs(position.w);
	
	float size = 0.1;
	gs_texCoord = vec2(-1.0, -1.0);
	gl_Position = position + vec4(-size, -size * uAspectRatio, 0, 0);
	EmitVertex();
	gs_texCoord = vec2(1.0, -1.0);
	gl_Position = position + vec4( size, -size * uAspectRatio, 0, 0);
	EmitVertex();
	gs_texCoord = vec2(-1.0, 1.0);
	gl_Position = position + vec4(-size,  size * uAspectRatio, 0, 0);
	EmitVertex();
	gs_texCoord = vec2(1.0, 1.0);
	gl_Position = position + vec4( size,  size * uAspectRatio, 0, 0);
	EmitVertex();
	EndPrimitive();
}