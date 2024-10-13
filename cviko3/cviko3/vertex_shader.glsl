#version 330 core

layout(location = 0) in vec3 aPosition; // Pozice vrcholu
layout(location = 1) in vec3 aNormal;   // Norm�la pro osv�tlen� (pokud je pot�eba)

uniform mat4 model;       // Matice modelu
uniform mat4 view;        // Matice pohledu
uniform mat4 projection;  // Matice projekce

out vec3 FragPos; // Pozice fragmentu v prostoru sv�ta, pro osv�tlen�
out vec3 Normal;  // Norm�la pro osv�tlen�

void main()
{
    // V�po�et pozice ve sv�tov�m prostoru
    FragPos = vec3(model * vec4(aPosition, 1.0));
    
    // Transformace norm�ly
    Normal = mat3(transpose(inverse(model))) * aNormal; 

    // V�po�et pozice vrcholu v clip space
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
