#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "frontends.hpp"
#include "image.hpp"
#include "scene.hpp"

// TODO gamma correction / scaling.
void ImageFrontend::render_image(RenderOpts render_opts, Scene &scene,
                                 std::string outfile_path) {
    Renderer renderer(render_opts);
    renderer.start_render(scene);

    std::cout << "{0% " << std::string(render_opts.bar_length - 8, ' ')
              << " 100%}" << std::endl;
    std::cout << "{" << std::flush;
    auto start = std::chrono::steady_clock::now();

    std::vector<vec3f> *pixels = renderer.get_pixels();

    const int total_needed = renderer.m_render_opts.image_width
        * renderer.m_render_opts.image_height
        * renderer.m_render_opts.num_samples;

    // Draw a progress bar while rendering.
    int dot_delta = total_needed / render_opts.bar_length;
    int pixels_done = 0;
    int total_dots = 0;
    while (renderer.m_pixels_done < total_needed) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        pixels_done = renderer.m_pixels_done;
        int last_dot = total_dots * dot_delta;

        if (pixels_done - last_dot >= dot_delta) {
            int new_dots = (pixels_done - last_dot) / dot_delta;
            total_dots += new_dots;
            if (total_dots > render_opts.bar_length) {
                new_dots -= total_dots - render_opts.bar_length;
            }
            std::cout << std::string(new_dots, '.') << std::flush;
        }
    }

    renderer.stop_render(true);

    auto end = std::chrono::steady_clock::now();

    std::cout << "}" << std::endl;
    std::cout << "Traced image in " <<
        (std::chrono::duration_cast<std::chrono::milliseconds>
         (end - start).count() / 1000.0) << " seconds." << std::endl;

    std::cout << "Saving image to " << outfile_path << std::endl;
    write_png(outfile_path.c_str(), *pixels,
              renderer.m_render_opts.image_width,
              renderer.m_render_opts.image_height);
}

void OpenGLFrontend::render_scene(RenderOpts render_opts, Scene &scene) {
    Renderer renderer(render_opts);
    renderer.start_render(scene);

    std::vector<vec3f> *pixels = renderer.get_pixels();
    GLvoid* pixel_data = &((*pixels)[0]);

    GLFWwindow* win = glfw_setup(render_opts.image_width, render_opts.image_height);
    load_program();

    GLfloat verts[] =
    {
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f,
    };


    GLfloat tex_coords[] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    GLuint vert_vbo = 0;
    glGenBuffers(1, &vert_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLuint tex_vbo = 0;
    glGenBuffers(1, &tex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, render_opts.image_width,
                 render_opts.image_height, 0, GL_RGB, GL_FLOAT, pixel_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    float pixels_one_frame = render_opts.image_height * render_opts.image_width;
    while (!glfwWindowShouldClose(win)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(70));

        std::cout << "Pixels rendered: " << renderer.m_pixels_done << ", or ~"
                  << renderer.m_pixels_done / pixels_one_frame << " samples per pixel"
                  << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glfwSwapBuffers(win);
        glfwPollEvents();

        pixel_data = &((*pixels)[0]);
        glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, render_opts.image_width,
                     render_opts.image_height, 0, GL_RGB, GL_FLOAT, pixel_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int OpenGLFrontend::load_shader(std::string shader_text, GLenum shader_type)
{
    const GLchar* shader_source = shader_text.c_str();
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const GLchar **) &shader_source, NULL);
    glCompileShader(shader);

    // Shader error reporting
    GLint is_compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

    if(is_compiled == GL_FALSE) {
        GLint max_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_len);

        GLchar* infoLog = (GLchar*) malloc(max_len * sizeof(GLchar));
        glGetShaderInfoLog(shader, max_len, &max_len, infoLog);

        printf("%s:%s\n", shader_source, infoLog);

        glDeleteShader(shader);
        exit(EXIT_FAILURE);
    }

    return shader;
}

int OpenGLFrontend::load_program()
{
    GLuint vs = load_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fs = load_shader(fragment_shader, GL_FRAGMENT_SHADER);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);

    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    return shader_program;
}

// GLFW Callbacks
void error_callback(int error, const char* description)
{
    std::cerr << "Error " << error << ": " << description << std::endl;
}

GLFWwindow* OpenGLFrontend::glfw_setup(int win_res_x, int win_res_y)
{
    // Windowing setup
    if (!glfwInit()) {
        std::cerr << "ERROR: couldn't start GLFW3." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(win_res_x, win_res_y, "Opengl Demo",
            NULL, NULL);
    glfwSetErrorCallback(error_callback);

    if (!win) {
        std::cerr << "ERROR: couldn't open window.\n" << std::endl;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return win;
}
