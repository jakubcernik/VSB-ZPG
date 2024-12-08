#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 fragWorldPosition;
out vec3 fragWorldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    TexCoord = aTexCoord;
     fragWorldPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    
    // Calculate normal matrix from model matrix
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    
    // Transform normal to world space
    fragWorldNormal = normalize(normalMatrix * vertexNormal);

    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
