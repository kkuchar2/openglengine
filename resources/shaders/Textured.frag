#version 330 core

uniform vec4 color;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPosition;

in vec2 uv;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
    FragColor = texture(tex, uv);
}