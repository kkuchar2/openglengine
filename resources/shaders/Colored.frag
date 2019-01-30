#version 330 core

out vec4 FragColor;

in vec3 position;

void main()
{
   float m = position.z;
   float MAX_ITER = 80.0;
   float c = (255.0 - m * 255.0 / MAX_ITER) / 255.0;
   FragColor = vec4(c, c, c, 1.0);
}