#version 330 core

uniform sampler2D in_Texture;

in vec2 ex_TexCoord;

out vec4 FragColor;

void main()
{
  vec4 tex = texture(in_Texture, ex_TexCoord);
  FragColor = tex;
}
