#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec3 vPos;
out vec2 vTexCoord;

uniform mat4 uVpMat;
uniform mat4 uTransMat;
uniform vec4 uColor;
uniform sampler2D uTexture;


void main() {
	vTexCoord = aTexCoord;
	vPos = aPos;
	gl_Position = uVpMat * uTransMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


#type fragment
#version 330 core

in vec2 vTexCoord;
in vec3 vPos;

layout(location = 0)out vec4 FragColor;


uniform mat4 uVpMat;
uniform mat4 uTransMat;
uniform vec4 uColor;
uniform sampler2D uTexture;

void main() {
	FragColor = texture(uTexture, vTexCoord) * uColor;
}