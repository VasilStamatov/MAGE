#version 330 core

uniform mat4 in_Projection;

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexCoord;

out vec2 ex_TexCoord;

void main()
{
  gl_Position = in_Projection * vec4(in_Position, 0.0, 1.0);
  gl_Position.w = 1.0;
  ex_TexCoord = in_TexCoord;
}