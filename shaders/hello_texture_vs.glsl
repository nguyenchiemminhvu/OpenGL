#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out VS_OUT
{
	vec2 uv;
} vs_out;

void main()
{
	gl_Position = vec4(position.xyz, 1.0);

	vs_out.uv = uv;
}