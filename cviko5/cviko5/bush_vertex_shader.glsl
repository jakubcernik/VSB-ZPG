#version 330 core

// Vertex attributes
layout(location = 0) in vec3 vertexPosition;  // Model space
layout(location = 1) in vec3 vertexNormal;    // Model space

uniform mat4 modelMatrix;       // Model space -> World space
uniform mat4 viewMatrix;        // World space -> View (camera) space
uniform mat4 projectionMatrix;  // View space -> Clip space

// Outputs to fragment shader
out vec3 fragWorldPosition;     // World space
out vec3 fragWorldNormal;       // World space

void main()
{
    fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    fragWorldNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
