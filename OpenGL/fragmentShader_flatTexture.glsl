#version 330 core

layout(location=0) out vec4 out_FragmentColor;

uniform sampler2D myTexture;

in vec4 normal;
in vec4 lightDir;
in vec4 viewDir;
in vec2 textureCoord;

void main(void) {

    vec3 textureColor = texture(myTexture, textureCoord).rgb;

    out_FragmentColor = vec4(textureColor, 1.0);
}