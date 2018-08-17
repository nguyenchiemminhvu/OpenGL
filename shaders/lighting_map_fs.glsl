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

uniform float time;

uniform vec3 eyePos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// ambient
	ambient = light.ambient * vec3(texture(material.diffuse, fs_in.uv));

	// diffuse
	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(fs_in.position - light.position);
	float diff = max(0.0, dot(-lightDir, normal));
	diffuse = diff * light.diffuse * vec3(texture(material.diffuse, fs_in.uv));

	// specular
	vec3 reflectDir = reflect(lightDir, normal);
	vec3 viewDir = normalize(fs_in.position - eyePos);
	float spec = pow(max(0.0, dot(reflectDir, -viewDir)), material.shininess);
	specular = spec * light.specular * vec3(texture(material.specular, fs_in.uv));

	// output
	vec4 outputColor = vec4(ambient + diffuse + specular, 1.0);
	outputColor *= abs(sin(time * 2));
	gl_FragColor = outputColor;
}
