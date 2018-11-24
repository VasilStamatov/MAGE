#version 330 core

uniform samplerCube in_Texture;

in vec3 ex_TexCoords;

out vec4 FragColor;

void main()
{    
  FragColor = texture(in_Texture, ex_TexCoords);
  // FragColor = vec4(ex_TexCoords, 1.0);
}