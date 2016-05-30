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
 * Sources:
 * https://en.wikipedia.org/wiki/Path_tracing
 * https://en.wikipedia.org/wiki/Rendering_equation
 */

// TODO kd-tree / octtree
// TODO less data movement

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

#include "tiny_obj_loader.h"
#include "png++/png.hpp"
#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3f vec3f;
typedef Eigen::Vector3d vec3i;

typedef struct {
    vec3f v1, v2, v3;
    vec3f norm;
    tinyobj::shape_t *shape_data;
    int index;
} Triangle;

typedef struct {
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> mats;
    std::vector<Triangle> tris;
} Scene;

void write_png(const char* filename, uint8_t* pixel_data,
        int img_width, int img_height)
{
    png::image<png::rgb_pixel> image(img_width, img_height);
    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for (png::uint_32 x = 0; x < image.get_width(); ++x) {
            image.set_pixel(x, y, png::rgb_pixel(
                    pixel_data[3 * (y * image.get_width() + x)],
                    pixel_data[3 * (y * image.get_width() + x) + 1],
                    pixel_data[3 * (y * image.get_width() + x) + 2]));
        }
    }
    image.write(filename);
}

void write_pixel(uint8_t* pixels, vec3f &color, int x, int y, int width)
{
    // assert(color.x() <= 1.0 && color.y() <= 1.0 && color.z() <= 1.0);
    pixels[3 * (y * width + x)] = 255 * color.x();
    pixels[3 * (y * width + x) + 1] = 255 * color.y();
    pixels[3 * (y * width + x) + 2] = 255 * color.z();
}

vec3f to_vec3f(float* a)
{
    vec3f v(a[0], a[1], a[2]);
    return v;
}

vec3f unit(vec3f &v)
{
    vec3f vn(v / v.norm());
    return vn;
}

vec3f vec_average(std::vector<vec3f> vecs)
{
    vec3f accum(0.0, 0.0, 0.0);
    for (vec3f v : vecs) {
        accum += v;
    }
    return accum / vecs.size();
}

void load_scene(std::vector<tinyobj::shape_t> &shapes,
        std::vector<tinyobj::material_t> &mats,
        std::vector<Triangle> &tris,
        std::string model_path, std::string model_name)
{
    std::string err;

    unsigned int flags =
        tinyobj::triangulation | tinyobj::calculate_normals;

    std::string obj_filename = model_path + model_name;
    bool success = tinyobj::LoadObj(shapes, mats, err, obj_filename.c_str(),
            model_path.c_str(), flags);

    if (!success) {
        std::cout << err << std::endl;
        std::cerr << "Model failed to load, Exiting." << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::cout << "Model loaded successfully." << std::endl;
    }

    for (int s=0; s < shapes.size(); s++) {
        tinyobj::shape_t shape = shapes[s];
        tinyobj::mesh_t mesh = shape.mesh;
        for (int i=0; i < mesh.indices.size(); i += 3) {
            unsigned int j1 = mesh.indices[i]*3;
            unsigned int j2 = mesh.indices[i+1]*3;
            unsigned int j3 = mesh.indices[i+2]*3;
            vec3f v1 = to_vec3f(&mesh.positions[j1]);
            vec3f v2 = to_vec3f(&mesh.positions[j2]);
            vec3f v3 = to_vec3f(&mesh.positions[j3]);
            vec3f norm = to_vec3f(&mesh.normals[j1]);

            Triangle tri = {
                .v1 = v1,
                .v2 = v2,
                .v3 = v3,
                .norm = norm,
                .shape_data = &(shapes[s]),
                .index = i
            };

            tris.push_back(tri);
        }
    }
}

// https://en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
float intersect(Triangle &tri, vec3f &ray, vec3f &eye)
{
    float EPSILON = 0.0001;

    vec3f e1, e2;
    vec3f p, q, r;
    float det, inv_det, u, v;
    float t;

    e1 = tri.v2 - tri.v1;
    e2 = tri.v3 - tri.v1;

    p = ray.cross(e2);
    det = e1.dot(p);

    if (det > -EPSILON && det < EPSILON) return 0;

    inv_det = 1.0 / det;
    r = eye - tri.v1;
    u = r.dot(p) * inv_det;

    if (u < 0.0 || u > 1.0) return 0;

    q = r.cross(e1);
    v = ray.dot(q) * inv_det;

    if (v < 0.0 || u + v > 1.0) return 0;

    t = e2.dot(q) * inv_det;

    if (t > EPSILON) {
        return t;
    } else {
        return 0;
    }
}

vec3f rand_hemisphere_vec(vec3f &norm)
{
    vec3f randy = Eigen::Vector3f::Random();
    if (randy.dot(norm) < 0) {
        randy = -randy;
    }
    return unit(randy);
}

vec3f trace(Scene &scene, vec3f ray, vec3f eye,
        int bounce=0, int max_bounces=3)
{
    vec3f out_color(0.49, 0.75, 0.93); // Sky blue.
    float cl_dist = std::numeric_limits<float>::infinity();
    Triangle *cl_tri;

    // Find which triangle (if any) our ray hits.
    bool hit = false;
    for (int t=0; t < scene.tris.size(); t++) {
        Triangle &tri = scene.tris[t];
        float dist = intersect(tri, ray, eye);

        if (dist < cl_dist && dist != 0) {
            hit = true;
            cl_dist = dist;
            cl_tri = &(scene.tris[t]);
        }
    }

    // If the ray hit a triangle, compute the output color.
    if (hit) {
        tinyobj::mesh_t mesh = cl_tri->shape_data->mesh;
        tinyobj::material_t mat = scene.mats[
            mesh.material_ids[cl_tri->index / 3]];

        // Return black if we've bounced around enough.
        if (bounce > max_bounces) {
            return vec3f(0.0, 0.0, 0.0);
        }

        // Material properties
        vec3f ip = eye + cl_dist * ray;
        vec3f emittance = to_vec3f(mat.emission);
        vec3f reflectance = to_vec3f(mat.specular);
        vec3f &norm = cl_tri->norm;

        // Reflect in a random direction on the normal's unit hemisphere.
        vec3f reflect_dir = rand_hemisphere_vec(norm);

        // Calculate BRDF
        float cos_theta = norm.dot(-ray);
        vec3f brdf = 2 * reflectance * cos_theta;
        vec3f reflected_amt = trace(scene, reflect_dir, ip, bounce + 1);

        // Final color
        out_color = emittance + (brdf.cwiseProduct(reflected_amt));
    }

    return out_color;
}

int main(int argc, char* argv[])
{
    // Pathtracer settings
    int num_samples = 200; // Number of samples per pixel
    float fov = M_PI / 5.0; // Camera field of view

    // REMINDER: Make dimensions different to find bugs.
    int width = 256,
        height = width;
    uint8_t pixels[height*width*3];

    // Default background color.
    uint8_t sky_blue[3] = {126, 192, 238};
    for (int i = 0; i < width*height*3; i++) {
        pixels[i] = sky_blue[i % 3];
    }

    // For random vectors
    srand(time(NULL));

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> mats;
    std::vector<Triangle> tris;

    Scene scene = {shapes, mats, tris};

    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    // Debugging Files.
    // std::string model_path = "";
    // std::string model_name = "test.obj";

    std::string model_path = "objs/";
    std::string model_name = "CornellBox-Original.obj";

    std::cout << "Loading model " << model_path << model_name << std::endl;
    load_scene(scene.shapes, scene.mats, scene.tris, model_path, model_name);

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

            vec3f ray(u, v, -1.0);
            vec3f rayn = unit(ray);
            vec3f eye(0, 1.0, 4.0);

            std::vector<vec3f> samples;
            for (int i=0; i < num_samples; i++) {
                samples.push_back(trace(scene, rayn, eye));
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
