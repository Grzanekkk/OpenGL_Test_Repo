#shader vertex
#version 330 core

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vertex_position;
    UV = vertexUV;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 UV;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, UV);
};