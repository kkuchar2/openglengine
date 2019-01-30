#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 UV;

out vec2 TexCoords;

void main()
{
    TexCoords = UV;
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}