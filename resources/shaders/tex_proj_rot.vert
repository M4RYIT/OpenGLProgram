#version 450 core
layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 vert_uv;

out vec2 vert_uv_out;

uniform float aspect_ratio;
uniform float fov;
uniform float near;
uniform float far;

uniform vec3 obj_pos;
uniform vec3 obj_rot;
uniform vec3 obj_scale;

vec3 perspective(vec3 pos)
{
    float fov_factor = tan(radians(fov * 0.5f));
    
    vec3 persp;   
    persp.x = (pos.x / -pos.z) / (fov_factor * aspect_ratio);
    persp.y = (pos.y / -pos.z) / fov_factor;    
    persp.z = ((-pos.z - near) / (far - near)) * 2 - 1;
    return persp;
}

vec3 scale(vec3 v, vec3 scale_factor)
{
    vec3 scaled_v;
    scaled_v.x = v.x * scale_factor.x;
    scaled_v.y = v.y * scale_factor.y;
    scaled_v.z = v.z * scale_factor.z;
    return scaled_v;
}

vec3 rotate(vec3 v, int axis, float angle)
{
    float rad = radians(angle);
    int index_1 = (axis + 1)%3;
    int index_2 = (axis + 2)%3;
    
    vec3 rotated_v = v;    
    rotated_v[index_1] = cos(rad) * v[index_1] - sin(rad) * v[index_2];
    rotated_v[index_2] = sin(rad) * v[index_1] + cos(rad) * v[index_2];
    return rotated_v;
}

void main() 
{
    vec3 mod_pos = scale(vert_pos, obj_scale);
    
    mod_pos = rotate(mod_pos, 0, obj_rot.x);
    mod_pos = rotate(mod_pos, 1, obj_rot.y);
    mod_pos = rotate(mod_pos, 2, obj_rot.z);

    mod_pos.x += obj_pos.x;
    mod_pos.y += obj_pos.y;
    mod_pos.y += -obj_pos.z;

    mod_pos = perspective(mod_pos);
    
    gl_Position = vec4(mod_pos, 1.f);

    vert_uv_out = vert_uv;
}