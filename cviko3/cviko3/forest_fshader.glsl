#version 330 core
in vec3 FragNormal;

out vec4 FragColor;

void main() {
    // Normálové barvy pro lepší vizualizaci
    vec3 color = normalize(FragNormal) * 0.5 + 0.5; // Posun na rozsah 0-1
    FragColor = vec4(color, 1.0);
}
