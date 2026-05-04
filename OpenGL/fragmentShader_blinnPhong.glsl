#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform float shininess;

in vec4 normal;
in vec4 lightDir;
in vec4 viewDir;

void main(void)
{
  vec3 n = normalize(normal.xyz);
  vec3 light = normalize(lightDir.xyz);
  vec3 view = normalize(viewDir.xyz);

  float diff = max(dot(n, light), 0.0);
  vec3 diffuse = diffuseComponent * diff;

  vec3 h = normalize(light + view);
  float spec = pow(max(dot(n,h), 0.0), shininess);
  vec3 specular = specularComponent * spec;

  vec3 ambient = 0.2 * diffuseComponent;
  vec3 finalColor = ambient + diffuse + specular;

  fragmentColor = vec4(finalColor, 1.0);
}
