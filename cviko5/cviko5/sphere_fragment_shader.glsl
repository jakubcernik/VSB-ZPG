#version 330 core

in vec3 FragPos;  // Pozice fragmentu
in vec3 Normal;   // Normála fragmentu

out vec4 FragColor;

uniform vec3 lightPos;      // Pozice svìtla
uniform vec3 viewPos;       // Pozice kamery (pozorovatele)
uniform vec3 lightColor;    // Barva svìtla
uniform vec3 objectColor;   // Barva objektu

void main()
{
    // Ambientní nasvícení
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Difúzní nasvícení
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Spekulární nasvícení
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Výsledná barva
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
