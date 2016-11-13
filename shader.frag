#version 330

in vec2 tex_coord;
uniform sampler2D tex;

void main()
{
    gl_FragColor = texture(tex, tex_coord);
}
