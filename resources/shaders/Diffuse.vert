#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 color;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in vec3 normal;

out vec2 uv;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vCoord, 1.0);
    FragPos = vec3(modelMatrix * vec4(vCoord, 1.0));
    uv = uvCoord;
    Normal = normal;
}