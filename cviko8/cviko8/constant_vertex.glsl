#version 330 core
layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;       // Model space -> World space
uniform mat4 viewMatrix;        // World space -> View (camera) space
uniform mat4 projectionMatrix;  // View space -> Clip space

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}
