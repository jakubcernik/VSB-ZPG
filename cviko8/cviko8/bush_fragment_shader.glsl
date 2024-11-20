#version 330 core

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float angle; // Cutoff angle in degrees
    int type; // 0 = point light, 1 = spotlight
};

#define MAX_LIGHTS 10

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 viewPos;
uniform vec3 objectColor;

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

out vec4 FragColor;

void main() {
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0;

        if (lights[i].type == 0) {
            // Point light
            lightDir = normalize(lights[i].position - fragWorldPosition);
            float distance = length(lights[i].position - fragWorldPosition);
            attenuation = 1.0 / (0.3 + 0.005 * distance + 0.0001 * (distance * distance));
        } else if (lights[i].type == 1) {
            // Spotlight
            lightDir = normalize(lights[i].position - fragWorldPosition);
            float distance = length(lights[i].position - fragWorldPosition);
            attenuation = 1.0 / (0.3 + 0.05 * distance + 0.0001 * (distance * distance));
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float cutoff = cos(radians(lights[i].angle));
            
            if (theta < cutoff) {
                attenuation = 0.0;
            }
        }

        // Ambient
        vec3 ambient = 0.1 * lights[i].color * objectColor;

        // Diffuse
        vec3 norm = normalize(fragWorldNormal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * objectColor;

        // Specular
        vec3 viewDir = normalize(viewPos - fragWorldPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = 0.3 * spec * lights[i].color * objectColor;

        result += ambient + (diffuse + specular) * attenuation;
    }

    result = clamp(result, 0.0, 1.0);

    FragColor = vec4(result, 1.0);
}
