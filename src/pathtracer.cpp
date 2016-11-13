/*
 * A pathtracer. This is a successor to a raytracer I wrote a few years ago.
 * Hopefully I can get some even cooler pictures out of this one. This time
 * around I'm using libraries for wavefront .obj loading, .png writing, and
 * vector math, whereas before they were hand rolled. Much nicer this way.
 *
 * Requires: tinyobjloader (included), Eigen, png++, soil,
 *           OpenGL 3.3 (for live-render), glfw, glew
 *
 * Building: Only tested on Linux. See Makefile.
 *
 * Related:
 * - Metropolis light transport
 * - Volumetric Pathtracing
 * - PBRT book
 *
 * References:
 * https://en.wikipedia.org/wiki/Path_tracing
 * https://en.wikipedia.org/wiki/Rendering_equation
 * http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml
 * https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
 * http://www.iquilezles.org/www/articles/simplepathtracing/simplepathtracing.htm
 *
 * Other cool projects:
 * http://raytracey.blogspot.com/2016/01/gpu-path-tracing-tutorial-3-take-your.html
 *
 * Author: Chris Laverdiere, 2016
 */

// TODO look at logging libraries
// https://github.com/easylogging/easyloggingpp
// https://github.com/easylogging/easyloggingpp
// OPT: opencl
// NEXT: Opengl live render (tex quad)
// TODO: Moving camera in live render
// TODO: RTR math
// TODO: Cache opts

#include "getopt.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "scene.hpp"
#include "renderer.hpp"
#include "frontends.hpp"

void show_help()
{
    std::cout <<
        "Usage: ./pathtracer [options]\n"
        "Flags: -h: Print this help.\n"
        "       -i: Input model file.\n"
        "       -o: Output image file.\n"
    << std::endl;
}

int main(int argc, char* argv[])
{
    std::string model_name;
    std::string output_name;
    std::stringstream argparse_errors;
    bool real_time = false;

    char cli_opt = 0;
    while ((cli_opt = getopt(argc, argv, "hi:o:r")) != -1) {
        switch (cli_opt) {
            case 'i':
                model_name.assign(optarg);
                break;
            case 'o':
                output_name.assign(optarg);
                break;
            case 'r':
                real_time = true;
                break;
            case 'h':
                show_help();
                std::exit(EXIT_SUCCESS);
                break;
        }
    }

    if (model_name.empty()) {
        argparse_errors << "You must specify an input model with -i <model>"
            << std::endl;
    }

    if (output_name.empty()) {
        argparse_errors << "You must specify an output image with -o <image>"
            << std::endl;
    }

    if (!(argparse_errors.rdbuf()->in_avail() == 0)) {
        std::cerr << argparse_errors.str() << std::endl;
        std::cerr << "Invalid flags given. Use -h for usage info."
            << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // TODO Set through config
    vec3f look_eye(0, 1.0, 4.0);
    vec3f look_dir(0.0, 0, -1.0);
    vec3f up_dir(0, 1.0, 0.0);

    // Pathtracer settings
    RenderOpts render_opts =
    {
        .image_width = 256,
        .image_height = 256,
        .num_samples = 30,
        .num_bounces = 3,
        .num_threads = 9,
        .bar_length = 72,
        .fov = M_PI / 5.0,
        .cam_up = up_dir,
        .cam_eye = look_eye,
        .cam_at = look_dir,
    };

    Renderer renderer(render_opts);

    std::cout << "Preprocessing scene" << std::endl;
    Scene scene(model_name);

    if (real_time) {
        std::cout << "Using OpenGL context for rendering." << std::endl;
        OpenGLFrontend rendering_frontend;
        rendering_frontend.render_scene(render_opts, scene);
    } else {
        std::cout << "Rendering to PNG image." << std::endl;
        ImageFrontend rendering_frontend;
        rendering_frontend.render_image(render_opts, scene, output_name);
    }

    return 0;
}
