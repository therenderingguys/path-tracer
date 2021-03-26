#version 330 core
out vec4 FragColor;
in vec2 u_texture;

uniform sampler2D o_texture;

void main()
{
    FragColor = texture(o_texture, u_texture);
}
