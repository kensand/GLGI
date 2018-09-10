#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;
layout( location = 2 ) in vec4 vColor;
layout( location = 3 ) in vec2 vTex;

uniform mat4 mvpShadowMatrix;

void main()
{
	gl_Position = mvpShadowMatrix * vec4(vPosition, 1.0);
	
}

