#version 450 core
out vec4 frag_color;

in vec2 vert_uv_out;
in vec3 world_pos_out;
in vec3 world_norm_out;

layout (binding = 0) uniform sampler2D tex;

uniform vec3 point_light_pos;
uniform vec3 camera_pos;
uniform float ambient_factor;
uniform float specular_factor;
uniform vec4 light_col;
uniform float light_intensity;

void main() 
{
    vec3 tex_col = texture(tex, vert_uv_out).xyz;

    //Ambient
    vec3 ambient = tex_col * ambient_factor;

    //Diffuse
    vec3 light_dir = normalize(point_light_pos - world_pos_out);
    vec3 norm_n = normalize(world_norm_out);
    float diff_str = max(dot(norm_n, light_dir), 0.f);
    vec3 diffuse = light_col.xyz * diff_str * light_intensity;

    //Specular
    vec3 eye_dir = normalize(camera_pos - world_pos_out);
    vec3 refl_dir = reflect(-light_dir, norm_n);
    float spec_str = max(dot(eye_dir, refl_dir), 0.f);
    float spec_fact = pow(spec_str, specular_factor);
    vec3 specular = vec3(1.f, 1.f, 1.f) * spec_fact;

    vec3 phong = ambient + diffuse + specular;

    float d = distance(point_light_pos, world_pos_out);
    float attenuation = 1.f / (1.f + d * d);
    phong *= attenuation;

    frag_color = vec4(phong, 1.f);
}