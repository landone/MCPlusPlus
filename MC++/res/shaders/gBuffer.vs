#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 transMatrix, rotMatrix, viewMatrix;
uniform bool gui;

void main(){

	FragPos = vec3(transMatrix * vec4(position, 1.0));
	TexCoords = texCoord;
	if (gui){
		gl_Position = vec4(FragPos, 1.0);
	} else {
		Normal = vec3(rotMatrix * vec4(normal, 1.0));
		gl_Position = viewMatrix * vec4(FragPos, 1.0);
	}

}