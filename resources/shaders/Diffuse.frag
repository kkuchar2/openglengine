#version 330 core

uniform vec4 color;
uniform float time;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec2 uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main()
{

  float ambientStrength = 0.2;
  vec3 ambient = ambientStrength * lightColor;



  vec3 norm = normalize(Normal);
  vec3 lightDir = lightPos - FragPos;

  float d = distance(lightPos, FragPos);
  float attenuation = clamp( 1.0 / (1.0 + 0.1 * d), 0.0, 1.0);;

  lightDir = normalize(lightDir);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * vec3(color);

  FragColor = vec4(attenuation * result, 1.0);
}