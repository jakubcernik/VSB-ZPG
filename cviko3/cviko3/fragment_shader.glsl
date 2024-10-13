#version 330 core

in vec3 FragPos; // Pozice fragmentu ze svìta
in vec3 Normal;  // Normála ze svìta

uniform vec3 lightPos;   // Pozice svìtla ve svìtovém prostoru
uniform vec3 viewPos;    // Pozice kamery pro výpoèet osvìtlení
uniform vec3 objectColor; // Barva objektu

out vec4 FragColor;

void main()
{
    // Ambientní složka
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objectColor;

    // Difuzní osvìtlení
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * objectColor;

    // Spekulární osvìtlení (volitelnì)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * objectColor;

    // Výsledná barva
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
