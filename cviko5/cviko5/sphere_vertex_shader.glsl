#version 330 core

layout (location = 0) in vec3 aPos;       // Pozice vrcholu
layout (location = 1) in vec3 aNormal;    // Normála vrcholu

out vec3 FragPos;         // Pozice fragmentu ve svìtovém prostoru
out vec3 Normal;          // Normála fragmentu ve svìtovém prostoru

uniform mat4 model;       // Modelová matice
uniform mat4 view;        // Pohledová matice
uniform mat4 projection;  // Projekèní matice

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; 

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
