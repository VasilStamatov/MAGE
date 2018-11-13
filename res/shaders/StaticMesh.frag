#version 120

//uniform sampler2D in_Texture;

varying vec2 ex_TexCoord;
varying vec4 ex_Color;

void main()
{
  //vec4 tex = texture2D(in_Texture, ex_TexCoord);
  gl_FragColor = ex_Color;
}
