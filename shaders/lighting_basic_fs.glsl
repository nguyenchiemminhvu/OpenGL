#version 330 core

in VS_OUT
{
	vec3 position;
	vec3 normal;
} fs_in;

uniform vec3 eyePos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 fragColor;

void main()
{
	// ambient
	float ambientStrength = 0.1;
	vec3 ambient = lightColor * ambientStrength;

	// diffuse
	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(fs_in.position - lightPos);
	float diffuseStrength = max(dot(normal, -lightDir), 0.0);
	vec3 diffuse = diffuseStrength * lightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(fs_in.position - eyePos);
	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(-viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = specularStrength * spec * lightColor;

	gl_FragColor = vec4((ambient + diffuse + specular) * fragColor, 1.0);
}
