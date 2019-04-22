#version 330 core

uniform mat4 m;
uniform mat4 vp;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 x;
layout (location = 4) in vec4 y;
layout (location = 5) in vec4 z;
layout (location = 6) in vec4 w;

out vec3 Normal;
out vec3 FragPos;
out vec3 TexCoords;

void main()
{
    mat4x4 m =  mat4(x, y, z, w);
    gl_Position = vp * m * vec4(vCoord, 1.0);
    FragPos = vec3(m * vec4(vCoord, 1.0));
    TexCoords = vCoord;
    Normal = mat3(transpose(inverse(m))) * normal;
}