#version 330 core

layout(location=0) out vec4 fragmentColor;

in vec4 normal;

void main(void)
{
  vec3 intensity = normalize(normal.xyz) * 0.5 + 0.5;
  fragmentColor = vec4(intensity, 1.0);
}