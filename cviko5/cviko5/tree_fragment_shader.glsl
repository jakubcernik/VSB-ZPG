#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;   // Pozice svìtla
uniform vec3 viewPos;    // Pozice kamery
uniform vec3 lightColor; // Barva svìtla
uniform vec3 objectColor; // Barva objektu

void main()
{
    // Zvýšení ambientní složky
    float ambientStrength = 0.3;  // Pùvodní hodnota mùže být nižší
    vec3 ambient = ambientStrength * lightColor;
    vec3 objectColor = vec3(0.3f, 0.8f, 0.2f);
    
    // Difúzní složka
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Zvýšení spekulární složky
    float specularStrength = 1.0;  // Pùvodní hodnota mùže být nižší
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Mùžete experimentovat i s exponentem (32) pro ostrost
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
