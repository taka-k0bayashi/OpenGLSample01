#version 450 core

layout(vertices = 3) out;

uniform float scale;

const float Outer = 5.0;
const float Inner = 5.0;

layout(location = 0)in vec3 in_color[];
layout(location = 0)out vec3 out_color[];

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    float d = clamp((scale - 1) * 30 + 1, 1.0, 20.0);

    gl_TessLevelOuter[0] = d;
    gl_TessLevelOuter[1] = d;
    gl_TessLevelOuter[2] = d;

    gl_TessLevelInner[0] = d;

    out_color[gl_InvocationID] = in_color[gl_InvocationID];
}