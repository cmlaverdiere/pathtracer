/*
 * A pathtracer. This is a successor to a raytracer I wrote a few years ago.
 * Hopefully I can get some even cooler pictures out of this one. This time
 * around I'm using libraries for wavefront .obj loading, .png writing, and
 * vector math, whereas before they were hand rolled. Much nicer this way.
 *
 * Requires: tinyobjloader (included), Eigen, png++
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
 *
 * Author: Chris Laverdiere, 2016
 */

// OPT: GPU (drawpix)
// OPT: opencl
// OPT: Cache design

#include "getopt.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "scene.hpp"

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

    char cli_opt = 0;
    while ((cli_opt = getopt(argc, argv, "hi:o:")) != -1) {
        switch (cli_opt) {
            case 'i':
                model_name.assign(optarg);
                break;
            case 'o':
                output_name.assign(optarg);
                break;
            case 'h':
                show_help();
                std::exit(EXIT_SUCCESS);
                break;
        }
    }

    if (model_name.empty()) {
        argparse_errors << "You must specify an input model with -i <model>" << std::endl;
    }

    if (output_name.empty()) {
        argparse_errors << "You must specify an output image with -o <image>" << std::endl;
    }

    if (!(argparse_errors.rdbuf()->in_avail() == 0)) {
        std::cerr << argparse_errors.str() << std::endl;
        std::cerr << "Invalid flags given. Use -h for usage info." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // TODO Set through config
    vec3f look_eye(0, 1.0, 4.0);
    vec3f look_dir(0.0, 0, -1.0);
    vec3f up_dir(0, 1.0, 0.0);
    Ray look_at = { look_eye, look_dir };
    Camera camera(look_at, up_dir);

    // Pathtracer settings
    RenderOpts render_opts =
    {
        .image_width = 196,
        .image_height = 196,
        .num_samples = 30,
        .num_bounces = 3,
        .x_threads = 4,
        .y_threads = 4,
        .fov = M_PI / 5.0,
    };

    std::cout << "Preprocessing scene" << std::endl;
    Scene scene(model_name, render_opts, camera);

    std::cout << "Rendering scene" << std::endl;
    scene.render(output_name);

    return 0;
}
