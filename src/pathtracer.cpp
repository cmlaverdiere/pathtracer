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

// OPT: threading / split into grid
// OPT: GPU

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include <libgen.h>
#include <libgen.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image.hpp"
#include "ray.hpp"
#include "scene.hpp"

int main(int argc, char* argv[])
{
    // Pathtracer settings
    int num_samples = 20; // Samples per pixel
    int num_bounces = 2; // Bounces per ray
    float fov = M_PI / 5.0; // Camera field of view

    // REMINDER: Make dimensions different to find bugs.
    int width = 128,
        height = width;
    uint8_t pixels[height*width*3];

    // For random vectors
    srand(time(NULL));

    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    // Debugging Files.
    // std::string model_path = "";
    // std::string model_name = "test.obj";

    std::string model_path = "objs/";
    std::string model_name = "CornellBox-Original.obj";

    /* std::string model_path = "/home/chris/devel/graphics/models/CornellBox/"; */
    /* std::string model_name = "CornellBox-Sphere.obj"; */

    Scene scene(model_path, model_name);

    float t = tan(fov / 2),
           b = -t,
           l = -t,
           r = t;

    int bar_width = 10;
    int dot_inc = height / bar_width;

    std::clock_t start;
    start = std::clock();

    std::cout << "Tracing paths" << std::endl;
    std::cout << "{";
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            float u = l + ((r - l) * (x + 0.5) / height);
            float v = b + ((t - b) * (y + 0.5) / width);
            v = -v;

            vec3f dir(u, v, -1.0);
            vec3f eye(0, 1.0, 4.0);
            Ray ray = { eye, unit(dir) };

            std::vector<vec3f> samples;
            for (int i=0; i < num_samples; i++) {
                samples.push_back(scene.shade(ray, 0, num_bounces));
            }

            vec3f average_sample = vec_average(samples);
            write_pixel(pixels, average_sample, x, y, width);
        }

        // Update progress bar.
        if (y % dot_inc == 0) {
            std::cout << "." << std::flush;
        }
    }
    std::cout << "}" << std::endl;

    std::cout << "Saving image to rt.png" << std::endl;
    write_png("rt.png", pixels, width, height);
    std::cout << "Traced image in " <<
        (std::clock() - start) / (float) (CLOCKS_PER_SEC) << " seconds."
        << std::endl;

    return 0;
}
