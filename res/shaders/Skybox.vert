#version 330 core

uniform mat4 in_Projection;
uniform mat4 in_View;

layout (location = 0) in vec3 in_Position;

out vec3 ex_TexCoords;

void main()
{
    ex_TexCoords = in_Position;
    vec4 pos = in_Projection * in_View * vec4(in_Position, 1.0);
    gl_Position = pos.xyww;
    // gl_Position = vec4(in_Position, 1.0);
}  