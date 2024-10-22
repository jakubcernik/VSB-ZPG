#version 330 core
out vec4 FragColor;
in vec3 Normal;

void main() {
    vec3 orangeTint = vec3(1.0, 0.8, 0.0);
    vec3 color = orangeTint * (normalize(Normal) * 0.5 + 0.5);
    FragColor = vec4(color, 1.0);
}
