#version 450 core
layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_uv;

out vec2 vert_uv_out;

uniform float aspect_ratio;

vec3 perspective(vec3 pos)
{
    float fov_factor = tan(radians(60.f * 0.5f));
    vec3 persp;
    persp.x = pos.x / (fov_factor * aspect_ratio);
    persp.y = pos.y / fov_factor;
    persp.z = 0.f;
    return persp;
}

void main() 
{
    vec3 proj_pos = perspective(vert_pos);
    gl_Position = vec4(proj_pos, 1.f);
    vert_uv_out = vert_uv;
}