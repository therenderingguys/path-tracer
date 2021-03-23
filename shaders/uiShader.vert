#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture;

out vec2 u_texture;

void main()
{
    gl_Position = vec4(a_position, 1.0);
    u_texture = a_texture;
}