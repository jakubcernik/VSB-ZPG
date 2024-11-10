#version 330 core

struct Light {
    vec3 position;
    vec3 color;
};

#define MAX_LIGHTS 10

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;

void main() {
    vec3 ambient = 0.1 * objectColor;

    vec3 result = ambient;
    vec3 norm = normalize(fragWorldNormal);

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - fragWorldPosition);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;

        float distance = length(lights[i].position - fragWorldPosition);
        //float attenuation = 1.0 / (distance * distance);
        float attenuation = 1.0 / (1.0f + 0.07f * distance + 0.017f * distance * distance);

        result += diffuse * attenuation;
    }

    FragColor = vec4(result, 1.0);
}
