#version 330 core

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float outerCutOff;
    int type; // 0 = point light, 1 = spotlight
};

#define MAX_LIGHTS 10

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 viewPos;

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

out vec4 FragColor;

void main() {
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float intensity;

        if (lights[i].type == 0) {
            // Point light
            lightDir = normalize(lights[i].position - fragWorldPosition);
            intensity = 1.0;
        } else if (lights[i].type == 1) {
            // Spotlight
            lightDir = normalize(lights[i].position - fragWorldPosition);
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;
            intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);
        }

        // Ambient
        float ambientStrength = 0.3;
        vec3 ambient = ambientStrength * lights[i].color;

        // Diffuse
        vec3 norm = normalize(fragWorldNormal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;

        // Specular
        float specularStrength = 1.0;
        vec3 viewDir = normalize(viewPos - fragWorldPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lights[i].color;

        result += (ambient + intensity * (diffuse + specular));
    }

    FragColor = vec4(result, 1.0);
}
