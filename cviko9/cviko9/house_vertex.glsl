
#version 330 core

// Vertex attributes
layout(location = 0) in vec3 vertexPosition;  // Model space
layout(location = 1) in vec3 vertexNormal;    // Model space
layout(location = 2) in vec2 vertexTexCoord; // Texture coordinates
layout(location = 3) in vec3 ts;  // tangent space

// Uniforms for transformations
uniform mat4 modelMatrix;       // Model space -> World space
uniform mat4 viewMatrix;        // World space -> View (camera) space
uniform mat4 projectionMatrix;  // View space -> Clip space

// Outputs to fragment shader
out vec3 fragWorldPosition;     // World space
out vec3 fragWorldNormal;       // World space
out vec2 fragTexCoord;          // Texture coordinates

void main()
{
    fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    fragWorldNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    fragTexCoord = vertexTexCoord;
    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
