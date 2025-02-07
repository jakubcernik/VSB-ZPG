#version 330 core
out vec4 FragColor;

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    vec3 norm = normalize(fragWorldNormal);
    vec3 lightDir = normalize(lightPos - fragWorldPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * objectColor;

    FragColor = vec4(diffuse, 1.0);
}
