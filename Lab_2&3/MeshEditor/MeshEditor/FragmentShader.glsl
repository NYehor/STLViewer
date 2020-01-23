#version 330 core
out vec4 FragColor;

in vec3 fragPosition;
in vec3 normal;

struct Light {
	bool isTurn;

    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

#define MAX_LIGHTS 8
uniform Light lights[MAX_LIGHTS];

uniform int numLights;
uniform vec3 color;

void main()
{
	vec3 N = normalize(normal);
	vec3 E = normalize(-fragPosition);

	vec3 resultColor = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < numLights; i++)
	{
		if(!lights[i].isTurn) continue;

		vec3 L = normalize(lights[i].position - fragPosition);
		vec3 R = normalize(-reflect(L, N));

		vec3 Ia = lights[i].ambient;
		Ia = clamp(Ia, 0.0, 1.0);

		vec3 Id = max(dot(N, L), 0.0) * lights[i].diffuse;
		Id = clamp(Id, 0.0, 1.0);

		vec3 Is = pow(max(dot(R, E), 0.01), 32) * lights[i].specular;
		Is = clamp(Is, 0.0, 1.0);

		resultColor += Ia + Id + Is;
	}
	
	FragColor = vec4(resultColor * color, 1.0);
};