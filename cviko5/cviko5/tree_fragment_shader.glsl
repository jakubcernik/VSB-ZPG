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
uniform float pointLightIntensity; // New uniform for point light intensity

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

out vec4 FragColor;

void main() {
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float intensity = 1.0;

        if (lights[i].type == 0) {
            // Point light
            lightDir = normalize(lights[i].position - fragWorldPosition);
            intensity = pointLightIntensity; // Use the new uniform for intensity
        } else if (lights[i].type == 1) {
            // Spotlight
            lightDir = normalize(lights[i].position - fragWorldPosition);
            float theta = dot(lightDir, normalize(-lights[i].direction));
            
            // Convert angle from degrees to radians
            float cutoff = cos(radians(lights[i].angle));
            
            // Calculate intensity based on cutoff angle
            intensity = (theta - cutoff) / (1.0 - cutoff);

            // If the fragment is outside the cutoff, set intensity to 0
            if (theta < cutoff) {
                intensity = 0.0;
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
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = 0.5 * spec * lights[i].color;

        result += ambient + intensity * (diffuse + specular);
    }

    FragColor = vec4(result, 1.0);
}
