#version 330 core

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;

uniform float time;
uniform vec4 color;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in vec3 normal;

out vec2 uv;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = mvp * vec4(vCoord, 1.0);
    FragPos = vCoord;
    uv = uvCoord;
    Normal = normal;
}