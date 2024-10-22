#version 330 core
in vec3 Normal;
out vec4 FragColor;

void main() {
    vec3 greenTint = vec3(0.0, 1.0, 0.2);
    vec3 color = greenTint * (normalize(Normal) * 0.5 + 0.5);
    FragColor = vec4(color, 1.0);
}
