#version 450

layout(location = 0) in vec3 vp;  // position
layout(location = 1) in vec3 vn;  // normal
layout(location = 2) in vec2 vt;  // texture space
layout(location = 3) in vec3 ts;  // tangent space

uniform mat4 modelMatrix;
out vec2 uv;

void main () {
	 uv = vt;
	 gl_Position = modelMatrix * vec4(vp, 1.0);
	 
}
