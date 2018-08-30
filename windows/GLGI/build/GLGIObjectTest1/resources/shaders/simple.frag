#version 400 core

in vec4 Color;
in vec2 Tex;

out vec4 fColor;

uniform mat4 mvpMatrix;
uniform sampler2DArray textureData;
uniform int textureID;

void main()
{
    fColor = texture(textureData, vec3(Tex.x, Tex.y, textureID));
}
