#version 330 core
out vec4 FragColor;

in vec3 fragWorldPosition;
in vec3 fragWorldNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 objectColor;

void main() {
	// Ambient lighting
    vec3 ambient = 0.2 * lightColor * objectColor;

    // Diffuse lighting
    vec3 norm = normalize(fragWorldNormal);
    vec3 lightDir = normalize(lightPos - fragWorldPosition);    // frag to light
    float diffIntensity = max(dot(norm, lightDir), 0.0);        // cos of angle between norm and lightDir
    vec3 diffuse = diffIntensity * lightColor * objectColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - fragWorldPosition);      // frag to camera
    vec3 reflectDir = reflect(-lightDir, norm);
    float specIntensity = max(dot(viewDir, reflectDir), 0.0);
    
    if (specIntensity >= 0.0) {
        specIntensity = pow(specIntensity, 32);
    } else {
        specIntensity = 0.0;
    }
    
    vec3 specular = lightColor * specIntensity;

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);
}