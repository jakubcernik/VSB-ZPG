
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord; // Texture coordinates

uniform mat4 modelMatrix;       // Model space -> World space
uniform mat4 viewMatrix;        // World space -> View (camera) space
uniform mat4 projectionMatrix;  // View space -> Clip space

out vec3 fragWorldPosition;     // World space
out vec3 fragWorldNormal;       // World space
out vec2 fragTexCoord;          // Texture coordinates

void main()
{
    fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    
    // Calculate normal matrix from model matrix
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    
    // Transform normal to world space
    fragWorldNormal = normalize(normalMatrix * vertexNormal);

    fragTexCoord = vertexTexCoord;
    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
