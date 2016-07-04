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
 */

// OPT: GPU or SIMD

#include <iostream>
#include <string>

#include "scene.hpp"

int main(int argc, char* argv[])
{
    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    // Pathtracer settings
    RenderOpts render_opts =
    {
        .image_width = 256,
        .image_height = 256,
        .num_samples = 100,
        .num_bounces = 5,
        .x_threads = 4,
        .y_threads = 4,
        .fov = M_PI / 5.0,
    };

    /* std::string model_path = "objs/"; */
    /* std::string model_name = "CornellBox-Original.obj"; */
    std::string model_path = "objs/";
    std::string model_name = "CornellBox-Sphere.obj";

    std::string outfile_path = "rt.png";

    std::cout << "Preprocessing scene" << std::endl;
    Scene scene(model_path, model_name);

    std::cout << "Rendering scene" << std::endl;
    scene.render(render_opts, outfile_path);

    return 0;
}
