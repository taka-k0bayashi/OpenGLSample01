#version 450 core

layout(location = 0)in vec3 out_color;
layout(location = 1)in vec4 position;

out vec4 fragment;

vec3 create_color(vec3 vec)
{
    vec3 color;
    if(vec.z > 0.666)
    {
        color = vec3(1.0, -3.0 * (vec.z -1.0), 0);
    }
    else if( vec.z > 0.333)
    {
        color = vec3(3 * vec.z -1, 1, 0);
    }
    else if( vec.z > 0.0)
    {
        color = vec3(0, 1, -3 * vec.z + 1);
    }
    else if(vec.z > -0.333)
    {
        color = vec3(0, 3 * vec.z + 1, 1);
    }
    else if(vec.z > -0.666)
    {
        color = vec3(-3 * vec.z - 1, 0, 1);
    }
    else
    {
        color = vec3(1, 0, 3 * vec.z + 3);
    }
    return color;
}

void main()
{
    //fragment = vec4(out_color, 1);
    fragment = vec4(create_color(position.xyz), 1);
}