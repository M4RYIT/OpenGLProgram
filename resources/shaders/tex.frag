#version 450 core
out vec4 frag_color;

in vec2 vert_uv_out;

layout (binding = 0) uniform sampler2D tex;

void main() 
{
    vec4 texel = texture(tex, vert_uv_out);
    frag_color = texel;
}