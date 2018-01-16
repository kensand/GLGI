
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;
layout( location = 2 ) in vec4 vColor;
layout( location = 3 ) in vec2 vTex;

out vec4 Color;
out vec2 Tex;


uniform mat4 mvpMatrix;

void
main()
{
	gl_Position = mvpMatrix * vec4(vPosition, 1.0);
	Color = vColor;
}
