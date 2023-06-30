#version 450 core

layout(vertices = 3) out;

uniform float scale;

layout(location = 0)in vec3 in_color[];
layout(location = 0)out vec3 out_color[];

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    const float tess_level = clamp((scale - 1) * 5 + 1, 1.0, 20.0);

    gl_TessLevelOuter[0] = tess_level;
    gl_TessLevelOuter[1] = tess_level;
    gl_TessLevelOuter[2] = tess_level;

    gl_TessLevelInner[0] = tess_level;

    out_color[gl_InvocationID] = in_color[gl_InvocationID];
}