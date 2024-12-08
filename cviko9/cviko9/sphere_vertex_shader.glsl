#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 modelMatrix;       // Model space -> World space
uniform mat4 viewMatrix;        // World space -> View (camera) space
uniform mat4 projectionMatrix;  // View space -> Clip space

out vec3 fragWorldPosition;
out vec3 fragWorldNormal;

void main() {
    fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    
    // Calculate normal matrix from model matrix
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    
    // Transform normal to world space
    fragWorldNormal = normalize(normalMatrix * vertexNormal);

    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
