#version 330 core

uniform vec4 color;
uniform float time;

out vec4 FragColor;

void main()
{
  FragColor = color;
}