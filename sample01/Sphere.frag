#version 450 core

layout(location = 0)in vec3 out_color;

out vec4 fragment;

void main()
{
    fragment = vec4(out_color, 1);
}