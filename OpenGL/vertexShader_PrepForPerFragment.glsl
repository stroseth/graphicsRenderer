#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_texCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

uniform vec4 lightPosWorld;

out vec4 normal;
out vec4 lightDir;
out vec4 viewDir;
out vec2 textureCoord;

void main(void)
{
  textureCoord = in_texCoord;
  
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));

  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  lightDir = normalize(lightPosWorld - vertexWorldPos);

  vec4 viewPos = vec4(inverse(viewMatrix) * vec4(0,0,0,1));
  viewDir = viewPos - vertexWorldPos;

  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}