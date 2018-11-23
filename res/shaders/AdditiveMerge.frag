#version 330 core

uniform sampler2D in_TextureA;
uniform sampler2D in_TextureB;

in vec2 ex_TexCoord;

out vec4 FragColor;

void main()
{
  vec4 texA = texture(in_TextureA, ex_TexCoord);
  vec4 texB = texture(in_TextureB, ex_TexCoord);
  FragColor = texA + texB;
}
