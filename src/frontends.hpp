#include <string>

// OpenGL libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// OpenGL Matrix math
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE GLM_SWIZZLE_XYZW

#include "renderer.hpp"
#include "scene.hpp"

class ImageFrontend {
public:
    void render_image(RenderOpts render_opts, Scene &scene, std::string outfile_path);
};

class OpenGLFrontend {
    // The shader files contain raw string literals.
    std::string vertex_shader =
        #include "shader.vert"
        ;
    std::string fragment_shader =
        #include "shader.frag"
        ;

    int load_shader(std::string filename, GLenum shader_type);
    int load_program();
    void update_pixels(float *pixel_data);
    GLFWwindow* glfw_setup(int win_res_x, int win_res_y);

public:
    void render_scene(RenderOpts render_opts, Scene &scene);
};

void error_callback(int error, const char* description);
