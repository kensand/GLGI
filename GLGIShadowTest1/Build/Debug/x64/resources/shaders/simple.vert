
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vNormal;
layout( location = 2 ) in vec4 vColor;
layout( location = 3 ) in vec2 vTex;

out vec4 Color;
out vec2 Tex;
out vec3 Normal;
out vec3 Position;

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat4 mMatrix;
uniform sampler2DArray textureData;
uniform int textureID;

void main()
{
	gl_Position = mvpMatrix * vec4(vPosition, 1.0);
	//Position = //mMatrix * vPosition;
	Position = vec3(mMatrix * vec4(vPosition, 1.0)); //this one kinda works, but view angle changes the level of diffuse light
	//Position = vPosition;
	Color = vColor;
	Tex = vTex;
	//mat3 NormMat = mat3(transpose(inverse(mMatrix)));
	mat3 NormMat = mat3(transpose(inverse(mMatrix)));
	Normal = normalize(NormMat * vNormal);
}
