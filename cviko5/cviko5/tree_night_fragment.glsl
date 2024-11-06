#version 330 core

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;

void main()
{
    vec3 ambient = 0.1 * objectColor;

    vec3 result = ambient;
    vec3 norm = normalize(Normal);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * lights[i].intensity;

        float distance = length(lights[i].position - FragPos);
        float attenuation = 1.0 / (distance * distance);

        result += diffuse * attenuation * 100000; // Debugging line
    }

    // Debug output
    if (result == ambient) {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red if no light is added
    } else {
        FragColor = vec4(result, 1.0);
    }
}