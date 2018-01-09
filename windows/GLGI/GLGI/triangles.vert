
#version 400 core

layout( location = 0 ) in vec4 vPosition;

uniform mat4 mvpMatrix;

void
main()
{
    gl_Position = mvpMatrix * vPosition;
}
