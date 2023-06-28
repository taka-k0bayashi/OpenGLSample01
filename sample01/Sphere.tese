#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 proj_mat;

layout(location = 0)in vec3 in_color[];
layout(location = 0)out vec3 out_color;

void main()
{
    vec4 point  = gl_in[0].gl_Position * gl_TessCoord.x +
				  gl_in[1].gl_Position * gl_TessCoord.y +
				  gl_in[2].gl_Position * gl_TessCoord.z;
	gl_Position = proj_mat * point;

	out_color =	  in_color[0] * gl_TessCoord.x +
				  in_color[1] * gl_TessCoord.y +
				  in_color[2] * gl_TessCoord.z;
}