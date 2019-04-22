#version 400

uniform mat4 m;
uniform mat4 vp;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;

out vec2 uv;

void main()
{
    gl_Position = vp * m * vec4(vCoord, 1.0);
    uv = uvCoord;
}