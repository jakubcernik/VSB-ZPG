#version 330 core
out vec4 FragColor;

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 objectColor;

// Material properties
uniform float Ra; // Ambient reflectivity
uniform float Rd; // Diffuse reflectivity
uniform float Rs; // Specular reflectivity

void main() {
    // Ambient lighting
    vec3 ambient = Ra * lightColor * objectColor;

    // Diffuse lighting
    vec3 norm = normalize(fragWorldNormal);
    vec3 lightDir = normalize(lightPos - fragWorldPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = Rd * diff * lightColor * objectColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - fragWorldPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = max(dot(viewDir, reflectDir), 0.0);
    if (spec >= 0.0) {
        spec = pow(spec, 32);
    } else {
        spec = 0.0;
    }
    vec3 specular = Rs * spec * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
