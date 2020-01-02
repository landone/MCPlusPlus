#version 400 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texMap;
uniform vec3 tint;
uniform bool gui;

void main(){

	vec4 origColor = texture(texMap, TexCoords);
	if(origColor.a < 1){
		discard;
	}

	gPosition = FragPos;
	gNormal = gui ? vec3(0.0) : normalize(Normal);
	gColor = origColor.xyz * tint;
	
}
