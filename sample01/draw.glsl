#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 proj_mat;

layout(location = 0) out vec3 out_color;

void main()
{
    gl_Position = proj_mat * vec4(position, 1);

    out_color = color;
}