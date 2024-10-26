#version 330 core

layout (location = 0) in vec3 aPos;       // Pozice vrcholu
layout (location = 1) in vec3 aNormal;    // Norm�la vrcholu

out vec3 FragPos;         // Pozice fragmentu ve sv�tov�m prostoru
out vec3 Normal;          // Norm�la fragmentu ve sv�tov�m prostoru

uniform mat4 model;       // Modelov� matice
uniform mat4 view;        // Pohledov� matice
uniform mat4 projection;  // Projek�n� matice

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; 

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
