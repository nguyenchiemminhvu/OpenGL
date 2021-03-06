#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 uv;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position.xyz, 1.0);

	vs_out.position = vec3(model * vec4(position, 1.0));
	vs_out.normal = mat3(transpose(inverse(model))) * normal;
	vs_out.uv = uv;
}