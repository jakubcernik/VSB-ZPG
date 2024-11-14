#version 330 core

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;    // camera position
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(fragWorldNormal);
    vec3 lightDir = normalize(lightPos - fragWorldPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - fragWorldPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 direction = vec3(1.0, 0.0, 0.0);
    float angle = cos(radians(30.0));
    vec3 result = (ambient + diffuse + specular) * objectColor;

    float alpha = dot(lightDir, normalize(direction));
    if (alpha > angle) { 
        FragColor = vec4(result, 1.0); //in
    } else {
        FragColor = vec4(ambient * objectColor, 1.0); //out
    }

    // Result
    //vec3 result = (ambient + diffuse + specular) * objectColor;
    //FragColor = vec4(result, 1.0);
}
