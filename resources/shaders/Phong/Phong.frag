#version 330 core

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPosition;

in vec2 uv;
in vec3 Normal;
in vec3 FragPos;
in vec4 fColor;

out vec4 FragColor;

void main()
{
  bool showNormals = false;

  float ambientStrength = 0.2;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(Normal);
  vec3 lightDir = lightPos - FragPos;

  float d = distance(lightPos, FragPos);
  float attenuation = clamp( 1.0 / (1.0 + 0.1 * d), 0.0, 1.0);

  lightDir = normalize(lightDir);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  float specularStrength = 1.0;
  vec3 viewDir = normalize(cameraPosition - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 result = (ambient + diffuse + specular) * vec3(fColor);

  if (showNormals) {
    FragColor = vec4(norm / 2 + vec3(0.5), 1.0);
  }
  else {
    FragColor = vec4(attenuation * result, 1.0);
  }
}