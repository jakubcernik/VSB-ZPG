#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;  // Modelov� matice

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(model * vec4(position, 1.0));
    Normal = normal;
    
    gl_Position = projection * view * model * vec4(position, 1.0);  // Vypo��t�n� kone�n� pozice vertexu
}
