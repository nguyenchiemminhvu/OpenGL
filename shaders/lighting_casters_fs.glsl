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
	sampler2D emission;

	float shininess;
};


struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};


struct FlashLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOffInner;
	float cutOffOuter;
};


uniform vec3 eyePos;

uniform Material material;

uniform int useSunLight;
uniform DirectionalLight sunLight;

uniform int usePointLight;
uniform PointLight pointLight;

uniform int useFlashLight;
uniform FlashLight flashLight;


void main()
{
	vec3 ambient, diffuse, specular;

	if (useSunLight == 1)
	{
		
	}

	if (usePointLight == 1)
	{
		
	}

	if (useFlashLight == 1)
	{
		
	}

	gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}
