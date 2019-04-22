#version 460 core

uniform mat4 m;
uniform mat4 vp;

layout (location = 0) in vec3 vCoord;

void main()
{
    gl_Position = vp * m * vec4(vCoord, 1.0);
}