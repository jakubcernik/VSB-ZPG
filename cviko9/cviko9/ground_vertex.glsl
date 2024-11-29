#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 fragWorldPosition;
out vec3 fragWorldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    TexCoord = aTexCoord;
    fragWorldPosition = vec3(modelMatrix * vec4(aPos, 1.0));
    fragWorldNormal = mat3(transpose(inverse(modelMatrix))) * aNormal;  

    gl_Position = projectionMatrix * viewMatrix * vec4(fragWorldPosition, 1.0);
}
