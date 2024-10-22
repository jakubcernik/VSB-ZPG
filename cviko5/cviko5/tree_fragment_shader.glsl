#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;   // Pozice sv�tla
uniform vec3 viewPos;    // Pozice kamery
uniform vec3 lightColor; // Barva sv�tla
uniform vec3 objectColor; // Barva objektu

void main()
{
    // Zv��en� ambientn� slo�ky
    float ambientStrength = 0.3;  // P�vodn� hodnota m��e b�t ni���
    vec3 ambient = ambientStrength * lightColor;
    vec3 objectColor = vec3(0.3f, 0.8f, 0.2f);
    
    // Dif�zn� slo�ka
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Zv��en� spekul�rn� slo�ky
    float specularStrength = 1.0;  // P�vodn� hodnota m��e b�t ni���
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // M��ete experimentovat i s exponentem (32) pro ostrost
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
