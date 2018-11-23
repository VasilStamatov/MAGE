#version 330 core

uniform sampler2D in_Texture;

in vec2 ex_TexCoord;

out vec4 FragColor;

void main()
{
  vec4 tex = texture(in_Texture, ex_TexCoord);
  
  if(tex.x > 0.9 || tex.y > 0.9 || tex.z > 0.9)
  {
    tex = vec4(0.5, 0.5, 0.5, 1);
  }
  else
  {
    tex = vec4(0, 0, 0, 1);
  }

  FragColor = tex;
}