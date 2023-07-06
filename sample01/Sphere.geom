#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 8) out;

uniform mat4 proj_mat;

layout(location = 0) in vec3 in_color[];
layout(location = 0) out vec3 out_color;

vec4 normalize3(vec4 vec)
{
    return vec4(normalize(vec.xyz), 1);
}

void main()
{
    gl_Position = proj_mat * normalize3(gl_in[0].gl_Position);
    out_color = in_color[0];
    EmitVertex();
    gl_Position = proj_mat * normalize3(gl_in[1].gl_Position);
    out_color = in_color[1];
    EmitVertex();
    gl_Position = proj_mat * normalize3(gl_in[2].gl_Position);
    out_color = in_color[2];
    EmitVertex();
    gl_Position = proj_mat * normalize3(gl_in[0].gl_Position);
    out_color = in_color[0];
    EmitVertex();


    EndPrimitive();

    return;
}