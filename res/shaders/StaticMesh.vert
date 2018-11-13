#version 120

uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec3 in_Color;
attribute vec2 in_TexCoord;

varying vec2 ex_TexCoord;
varying vec4 ex_Color;

void main()
{
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
  // ex_TexCoord = in_TexCoord;
  ex_Color = vec4(1.0, 1.0, 1.0, 1.0);
}

