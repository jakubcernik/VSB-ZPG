#version 450

in vec2 uv;

uniform sampler2D textureUnitID;

out vec4 frag_color;

void main () {
    frag_color = texture(textureUnitID, uv);
}

