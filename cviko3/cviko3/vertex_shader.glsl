#version 330 core

layout(location = 0) in vec3 aPosition; // Pozice vrcholu
layout(location = 1) in vec3 aNormal;   // Normála pro osvìtlení (pokud je potøeba)

uniform mat4 model;       // Matice modelu
uniform mat4 view;        // Matice pohledu
uniform mat4 projection;  // Matice projekce

out vec3 FragPos; // Pozice fragmentu v prostoru svìta, pro osvìtlení
out vec3 Normal;  // Normála pro osvìtlení

void main()
{
    // Výpoèet pozice ve svìtovém prostoru
    FragPos = vec3(model * vec4(aPosition, 1.0));
    
    // Transformace normály
    Normal = mat3(transpose(inverse(model))) * aNormal; 

    // Výpoèet pozice vrcholu v clip space
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
