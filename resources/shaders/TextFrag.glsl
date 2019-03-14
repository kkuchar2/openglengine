#version 330 core

uniform vec4 color;
uniform float time;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D tex;

in vec2 uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;



void main()
{
   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, uv).r);
   FragColor = vec4(color.rgb, 1.0) * sampled;
}