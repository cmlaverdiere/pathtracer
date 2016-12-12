R"(
#version 330

in vec2 tex_coord;
uniform sampler2D tex;

void main()
{
    gl_FragColor = pow(texture(tex, tex_coord), vec4(1 / 2.2));
}
)"
