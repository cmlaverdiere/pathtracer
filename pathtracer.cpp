/*
 * A pathtracer. This is a successor to a raytracer I wrote a few years ago.
 * Hopefully I can get some even cooler pictures out of this one. This time
 * around I'm using libraries for wavefront .obj loading, .png writing, and
 * vector math, whereas before they were hand rolled. Fuck that though.
 *
 * Requires: tinyobjloader (included), Eigen, png++
 *
 * See also:
 * - Metropolis light transport
 * - Volumetric Pathtracing
 * - PBRT book
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include <libgen.h>
#include <string.h>
#include <math.h>

#include "tiny_obj_loader.h"
#include "png++/png.hpp"
#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3f vec3f;
typedef Eigen::Vector3d vec3i;

typedef struct {
    vec3f v1, v2, v3;
} triangle_t;

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

void load_scene(std::vector<tinyobj::shape_t> &shapes,
        std::vector<tinyobj::material_t> &mats,
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
}

vec3f unit(vec3f v)
{
    vec3f vn(v / v.norm());
    return vn;
}

// https://en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
float intersect(triangle_t tri, vec3f ray, vec3f eye)
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

int main(int argc, char* argv[])
{
    // TODO make different to find bugs.
    int width = 256,
        height = width;
    uint8_t pixels[height*width*3];

    uint8_t sky_blue[3] = {126, 192, 238};
    for (int i = 0; i < width*height*3; i++) {
        pixels[i] = sky_blue[i % 3];
    }

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> mats;

    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    // std::string model_path = "/home/chris/devel/graphics/pathtracer/";
    // std::string model_name = "test.obj";

    std::string model_path = "/home/chris/devel/graphics/models/CornellBox/";
    std::string model_name = "CornellBox-Original.obj";

    std::cout << "Loading model " << model_path << model_name << std::endl;
    load_scene(shapes, mats, model_path, model_name);

    // IMPLEMENT
    // Pathtrace each pixel, sample multiple times.

    // TEMP triangle raytracer
    // NOTE assumes all triangles.

    // TODO briefly go over the trig for this.
    float fov = M_PI / 5.0;
    double t = tan(fov / 2);
    double b = -t;
    double l = -t;
    double r = t;

    std::cout << "Raytracing" << std::endl;
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            float closest_dist = std::numeric_limits<float>::infinity();
            vec3f closest_color = vec3f(0.1, 0.1, 0.1);

            // float u = (float) (x - width / 2) / (width / 2);
            // float v = (float) (y - height / 2) / (height / 2);

            float u = l + ((r - l) * (x + 0.5) / height);
            float v = b + ((t - b) * (y + 0.5) / width);

            v = -v;

            vec3f ray(u, v, -1.0);
            vec3f rayn = unit(ray);
            vec3f eye(0, 1.0, 4.0);

            // TODO refactor into trace fn
            for (tinyobj::shape_t shape : shapes) {
                tinyobj::mesh_t mesh = shape.mesh;
                for (int i=0; i < mesh.indices.size(); i += 3) {
                    int j1 = mesh.indices[i]*3;
                    int j2 = mesh.indices[i+1]*3;
                    int j3 = mesh.indices[i+2]*3;
                    vec3f v1(mesh.positions[j1],
                            mesh.positions[j1+1],
                            mesh.positions[j1+2]);
                    vec3f v2(mesh.positions[j2],
                            mesh.positions[j2+1],
                            mesh.positions[j2+2]);
                    vec3f v3(mesh.positions[j3],
                            mesh.positions[j3+1],
                            mesh.positions[j3+2]);
                    triangle_t tri = { v1, v2, v3 };

                    float dist = intersect(tri, rayn, eye);

                    if (dist < closest_dist && dist != 0) {
                        float* kd = mats[mesh.material_ids[i / 3]].diffuse;
                        vec3f norm(mesh.normals[j1],
                                mesh.normals[j1+1], mesh.normals[j1+2]);
                        vec3f light(0.0, 2.0, 0.0);
                        vec3f ip = eye + dist * rayn;
                        vec3f to_l = unit(light - ip);
                        float n_l = fabs(norm.dot(to_l));
                        closest_dist = dist;
                        closest_color = n_l * vec3f(kd[0], kd[1], kd[2]);
                    }
                }
            }

            pixels[3 * (y * width + x)] = 255 * closest_color.x();
            pixels[3 * (y * width + x) + 1] = 255 * closest_color.y();
            pixels[3 * (y * width + x) + 2] = 255 * closest_color.z();
        }
    }

    std::cout << "Writing png" << std::endl;
    write_png("rt.png", pixels, width, height);
    std::cout << "Done" << std::endl;

    return 0;
}
