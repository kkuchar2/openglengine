#version 330 core

uniform vec4 color;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in vec3 normal;

// Model matrix split
layout (location = 3) in vec4 x;
layout (location = 4) in vec4 y;
layout (location = 5) in vec4 z;
layout (location = 6) in vec4 w;

out vec2 uv;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    mat4x4 m =  mat4(x, y, z, w);
    gl_Position = projectionMatrix * viewMatrix *m * vec4(vCoord, 1.0);
    FragPos = vec3(m * vec4(vCoord, 1.0));
    uv = uvCoord;
    Normal = normal;
}