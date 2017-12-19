#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out VS_OUT
{
	vec2 uv;
} vs_out;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position.xyz, 1.0);

	vs_out.uv = uv;
}