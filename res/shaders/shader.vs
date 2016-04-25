#version 330

layout (location = 0) in vec2 texcoord;
layout (location = 1) in vec3 position;
layout (location = 2) in vec3 color;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 trans;

void main()
{
    Color = color;
    gl_Position = trans * vec4(position, 1.0);
    TexCoord = texcoord;
}