#version 400 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texMap;

void main(){
	
	vec4 origColor = texture(texMap, TexCoords);
	if(origColor.a < 1){
		discard;
	}
	FragColor = origColor;
	
}
