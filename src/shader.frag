R"(
#version 410 core

in vec2 tex_coord;
uniform sampler2D tex;
out vec4 FragColor;

void main()
{
    FragColor = pow(texture(tex, tex_coord), vec4(1.0 / 2.2));
}
)"
