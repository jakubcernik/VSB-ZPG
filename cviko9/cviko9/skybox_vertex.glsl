#version 450

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    mat4 view = viewMatrix;

    vec4 pos = projectionMatrix * view * vec4(aPos, 1.0);
    
    // Ensuring depth is set to 1.0 (far plane)
    gl_Position = pos.xyww;

    TexCoords = aPos;
}
