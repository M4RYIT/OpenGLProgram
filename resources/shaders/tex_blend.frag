#version 450 core
out vec4 frag_color;

in vec2 vert_uv_out;

layout (binding = 0) uniform sampler2D tex1;
layout (binding = 1) uniform sampler2D tex2;

uniform vec4 base_color;
uniform float blend_factor;

void main() 
{
    vec4 col_tex1 = texture(tex1, vert_uv_out);
    vec4 col_tex2 = texture(tex2, vert_uv_out);
    frag_color = mix(col_tex1, col_tex2, blend_factor);
    frag_color *= base_color;
}