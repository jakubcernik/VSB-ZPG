#version 450

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube UISky;

void main()
{
    FragColor = texture(UISky, TexCoords);
}
