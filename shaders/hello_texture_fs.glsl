#version 330 core

in VS_OUT
{
	vec3 color;
} fs_in;

void main()
{
	gl_FragColor = vec4(fs_in.color.xyz, 1.0);
}