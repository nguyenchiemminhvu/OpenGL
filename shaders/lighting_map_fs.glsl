#version 330 core

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 uv;
} fs_in;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};


struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


uniform vec3 eyePos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;



	gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}
