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

#include "aabb.hpp"
#include "image.hpp"
#include "kdtree.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "triangle.hpp"
#include "utils.hpp"
#include "vector.hpp"

// TODO Scene method?
vec3f shade(Scene &scene, Ray ray, int bounce=0, int max_bounces=3) {
    TriangleHit hit_data = scene.m_tree->hit(ray);
    Triangle* tri = hit_data.tri;
    float dist = hit_data.dist;

    if (tri == NULL) {
        return vec3f(0.0, 0.0, 0.0);
    }

    tinyobj::mesh_t mesh = tri->shape_data->mesh;
    tinyobj::material_t mat = scene.m_mats[
        mesh.material_ids[tri->index / 3]];

    // Return black if we've bounced around enough.
    if (bounce > max_bounces) {
        return vec3f(0.0, 0.0, 0.0);
    }

    // Material properties
    Ray reflect_ray;
    reflect_ray.pos = ray.pos + dist * ray.dir;
    vec3f emittance = to_vec3f(mat.emission);
    vec3f reflectance = to_vec3f(mat.diffuse);
    /* vec3f specular = to_vec3f(mat.specular); */
    vec3f &norm = tri->norm;

    // Reflect in a random direction on the normal's unit hemisphere.
    reflect_ray.dir = rand_hemisphere_vec(norm);

    // Calculate BRDF
    float cos_theta = norm.dot(-ray.dir);
    vec3f brdf = 2 * reflectance * cos_theta;
    vec3f reflected_amt = shade(scene, reflect_ray, bounce + 1,
            max_bounces);

    // For specular, reflect perfectly.
    /* Ray spec_reflect_ray; */
    /* vec3f spec_reflected_amt; */
    /* if (specular.norm() != 0.0) { */
    /*     spec_reflect_ray.pos = reflect_ray.pos; */
    /*     spec_reflect_ray.dir = ray.dir + (2 * cos_theta * norm); */
    /*     spec_reflected_amt = shade(scene, spec_reflect_ray, bounce + 1, */
    /*             max_bounces); */
    /* } */

    // Final color
    return emittance + brdf.cwiseProduct(reflected_amt);
    /* return emittance + brdf.cwiseProduct(reflected_amt + spec_reflected_amt); */
}

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
                samples.push_back(shade(scene, ray, 0, num_bounces));
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
