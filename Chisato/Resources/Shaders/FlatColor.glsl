#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 uVpMat;
uniform mat4 uTransMat;
out vec4 vColor;

void main() {

	vColor = aColor;
	gl_Position = uVpMat * uTransMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#type fragment
#version 330 core
out vec4 FragColor;
in vec4 vColor;
uniform mat4 uVpMat;
uniform mat4 uTransMat;
uniform vec4 uColor;
void main() {
	FragColor = uColor;
}