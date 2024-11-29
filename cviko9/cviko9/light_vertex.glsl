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

void main() {
    // Transform vertex position to world space
    fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    
    // Calculate the normal matrix from the model matrix
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    
    // Transform and normalize the normal to world space
    fragWorldNormal = normalize(normalMatrix * vertexNormal);

    // Final position of the vertex in clip space
    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
