#version 330 core

in vec3 FragPos; // Pozice fragmentu ze sv�ta
in vec3 Normal;  // Norm�la ze sv�ta

uniform vec3 lightPos;   // Pozice sv�tla ve sv�tov�m prostoru
uniform vec3 viewPos;    // Pozice kamery pro v�po�et osv�tlen�
uniform vec3 objectColor; // Barva objektu

out vec4 FragColor;

void main()
{
    // Ambientn� slo�ka
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objectColor;

    // Difuzn� osv�tlen�
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * objectColor;

    // Spekul�rn� osv�tlen� (voliteln�)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * objectColor;

    // V�sledn� barva
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
