#include <string>

#include "renderer.hpp"
#include "scene.hpp"

class ImageFrontend {
public:
    void render_image(RenderOpts render_opts, Scene &scene, std::string outfile_path);
};

class OpenGLFrontend {
public:
    void render_scene(RenderOpts render_opts, Scene &scene);
};
