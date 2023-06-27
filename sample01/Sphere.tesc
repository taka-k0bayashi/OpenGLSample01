#version 450 core

layout(vertices = 3) out;

const float Outer = 2.0;
const float Inner = 2.0;

layout(location = 0)in vec3 in_color[];
layout(location = 0)out vec3 out_color[];

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    gl_TessLevelOuter[0] = Outer;
    gl_TessLevelOuter[1] = Outer;
    gl_TessLevelOuter[2] = Outer;

    gl_TessLevelInner[0] = Inner;

    out_color[gl_InvocationID] = in_color[gl_InvocationID];
}