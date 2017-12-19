#version 330 core

in VS_OUT
{
	vec2 uv;
} fs_in;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	gl_FragColor = mix(texture(tex, fs_in.uv), texture(tex2, fs_in.uv), 0.5);
}