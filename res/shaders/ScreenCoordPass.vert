#version 330 core

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexCoord;

out vec2 ex_TexCoord;

void main()
{
  gl_Position = vec4(in_Position, 0, 1);
  ex_TexCoord = in_TexCoord;
}