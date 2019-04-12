#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;

out vec2 uv;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vCoord, 1.0);
    uv = uvCoord;
}