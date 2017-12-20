#version 330 core

in VS_OUT
{
	vec2 uv;
} fs_in;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, fs_in.uv);
}