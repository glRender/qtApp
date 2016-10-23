#version 330 core 
out vec4 color;   
in vec3 keyring_position; 
in vec2 keyring_uv; 
in float keyring_r; 
in float keyring_g; 
in float keyring_b; 
// uniform sampler2D texture0;
// uniform sampler2D texture1;

void main(void)
{
    // vec4 c = vec4(keyring_uv, 1.0, 1.0);
    // vec4 t0 = 0.9 * texture(texture0, keyring_uv);
    // vec4 t1 = texture(texture1, keyring_uv);
    // color = c;
    color = vec4(keyring_r, keyring_g, keyring_b, 1.0);

}