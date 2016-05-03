#version 330

layout (location = 0) in vec2 texcoord;
layout (location = 1) in vec3 position;
layout (location = 2) in vec3 normals;

out vec2 TexCoord;
out vec3 Normals;
out vec3 Vertex;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = model * vec4(position, 1.0);
    TexCoord = texcoord;
    Normals = normals;
    Vertex = position;
    FragPos = vec3(model * vec4(position, 1.0f));
}