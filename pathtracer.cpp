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
// DES: wrap Eigen

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

#define INF std::numeric_limits<float>::infinity()

typedef Eigen::Vector3f vec3f;
typedef Eigen::Vector3d vec3i;

// REF: move shape_data / index to shader
typedef struct {
    vec3f verts[3];
    vec3f norm;
    tinyobj::shape_t *shape_data;
    int index;

    vec3f& operator[] (const int index);
    vec3f midpoint();
} Triangle;

vec3f& Triangle::operator[] (const int index)
{
    return verts[index];
}

vec3f Triangle::midpoint()
{
    return (verts[0] + verts[1] + verts[2]) / 3.0;
}

// Axis aligned bounding box (AABB)
typedef struct {
    vec3f ll, ur;
} Box;

typedef struct {
    vec3f pos, dir;
} Ray;

typedef struct {
    Triangle* tri;
    float dist;
} HitData;

class KdTree {
    private:
        Box m_box;
        KdTree *m_left, *m_right;
        std::vector<Triangle> m_tris;

    public:
        KdTree(std::vector<Triangle> tris, int dim_split = 0,
                int max_tris = 3);
        HitData hit(Ray &ray);
};

class Scene {
    public:
        std::vector<tinyobj::shape_t> m_shapes;
        std::vector<tinyobj::material_t> m_mats;
        KdTree* m_tree;

        Scene(std::string model_path, std::string model_name);
};

vec3f to_vec3f(float* a);
vec3f unit(vec3f &v);
vec3f vec_average(std::vector<vec3f> vecs);
float intersect_tri(Triangle &tri, Ray &ray);
bool intersect_box(Box &box, Ray &ray);

Scene::Scene(std::string model_path, std::string model_name)
{
    std::string err;

    std::cout << "Loading model " << model_path << model_name << std::endl;
    unsigned int flags =
        tinyobj::triangulation | tinyobj::calculate_normals;

    std::string obj_filename = model_path + model_name;
    bool success = tinyobj::LoadObj(m_shapes, m_mats, err,
            obj_filename.c_str(), model_path.c_str(), flags);

    if (!success) {
        std::cout << err << std::endl;
        std::cerr << "Model failed to load, Exiting." << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::cout << "Model loaded successfully." << std::endl;
    }

    std::cout << "Constructing triangles" << std::endl;
    std::vector<Triangle> tris;
    for (int s=0; s < m_shapes.size(); s++) {
        tinyobj::shape_t shape = m_shapes[s];
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
                .verts[0] = v1,
                .verts[1] = v2,
                .verts[2] = v3,
                .norm = norm,
                .shape_data = &(m_shapes[s]),
                .index = i
            };

            tris.push_back(tri);
        }
    }

    std::cout << "Constructing KdTree" << std::endl;
    m_tree = new KdTree(tris);
}

// Naive BSP construction (midpoint)
// A tree is constructed with at most max_tris on each leaf.
// OPT: use SAH
// OPT: precalc midpoints
KdTree::KdTree(std::vector<Triangle> tris, int dim_split,
        int max_tris)
{
    // Leaf creation.
    if (tris.size() <= max_tris) {
        m_tris = tris; // PROFILE copy
        m_left = NULL;
        m_right = NULL;
        return;
    }

    // Internal node creation.

    // Precalculate min/max/average coordinate info.
    float midpoint_total = 0.0;
    float max_dims[3] = {0.0};
    float min_dims[3] = {INF};
    for (int i=0; i < tris.size(); i++) {
        for (int vert=0; vert < 3; vert++) {
            for (int dim=0; dim < 3; dim++) {
                float val = tris[i][vert][dim];
                if (max_dims[dim] < val) max_dims[dim] = val;
                if (min_dims[dim] > val) min_dims[dim] = val;
            }
        }
        midpoint_total += tris[i].midpoint()[dim_split];
    }

    // Find the average coordinate along dimension dim_split for left / right
    // tree separation.
    float dim_avg = midpoint_total / tris.size();

    // Use max / min dimensions for bounding box creation.
    vec3f lower_left = to_vec3f(min_dims);
    vec3f upper_right = to_vec3f(max_dims);
    m_box = { lower_left, upper_right };

    // Split the tree at the midpoint and construct each half.
    std::vector<Triangle> left_tris, right_tris;
    for (int i=0; i < tris.size(); i++) {
        if (tris[i].midpoint()[dim_split] < dim_avg) {
            left_tris.push_back(tris[i]);
        } else {
            right_tris.push_back(tris[i]);
        }
    }

    int next_dim = (dim_split + 1) % 3;
    m_left = new KdTree(left_tris, next_dim);
    m_right = new KdTree(right_tris, next_dim);
}

// TODO pass around shader info
HitData KdTree::hit(Ray &ray)
{
    // At leaf
    if (m_left == NULL && m_right == NULL) {
        HitData hit_data;
        float cl_dist = INF;
        Triangle *cl_tri = NULL;

        // Find which triangle (if any) our ray hits.
        bool hit = false;
        for (int t=0; t < m_tris.size(); t++) {
            Triangle &tri = m_tris[t];
            float dist = intersect_tri(tri, ray);

            if (dist < cl_dist && dist != 0) {
                hit = true;
                cl_dist = dist;
                cl_tri = &(m_tris[t]);
            }
        }

        hit_data.tri = cl_tri;
        hit_data.dist = cl_dist;
        return hit_data;
    }

    // At interior node
    else if (intersect_box(m_box, ray)) {
        HitData left_hit = m_left->hit(ray);
        HitData right_hit = m_right->hit(ray);
        if (left_hit.tri == NULL) {
            return right_hit;
        } else {
            return left_hit;
        }
    }

    HitData miss = { NULL, 0.0 };
    return miss;
}

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

// Modified slabs method from Real Time Rendering ch 16.7.1
// PROFILE: Branch all at once.
// OPT: Try without div by f.
bool intersect_box(Box &box, Ray &ray)
{
    float t_min = -INF;
    float t_max = INF;

    vec3f to_p1 = box.ll - ray.pos;
    vec3f to_p2 = box.ur - ray.pos;

    // TODO extra checks.
    for (int i=0; i<3; i++) {
        float f = ray.dir[i];
        float t1 = to_p1[i] / f;
        float t2 = to_p2[i] / f;

        if (t1 > t2) {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > t_min) t_min = t1;
        if (t2 < t_max) t_max = t2;
        if (t_min > t_max) return false;
        if (t_max < 0) return false;
    }

    return true;
}

// https://en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
// OPT: precalculate dominant triangle axis.
float intersect_tri(Triangle &tri, Ray &ray)
{
    float EPSILON = 0.0001;

    vec3f e1, e2;
    vec3f p, q, r;
    float det, inv_det, u, v;
    float t;

    e1 = tri[1] - tri[0];
    e2 = tri[2] - tri[0];

    p = ray.dir.cross(e2);
    det = e1.dot(p);

    if (det > -EPSILON && det < EPSILON) return 0;

    inv_det = 1.0 / det;
    r = ray.pos - tri[0];
    u = r.dot(p) * inv_det;

    if (u < 0.0 || u > 1.0) return 0;

    q = r.cross(e1);
    v = ray.dir.dot(q) * inv_det;

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

vec3f shade(Scene &scene, Ray ray, int bounce=0, int max_bounces=3) {
    HitData hit_data = scene.m_tree->hit(ray);
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
    vec3f &norm = tri->norm;

    // Reflect in a random direction on the normal's unit hemisphere.
    reflect_ray.dir = rand_hemisphere_vec(norm);

    // Calculate BRDF
    float cos_theta = norm.dot(-ray.dir);
    vec3f brdf = 2 * reflectance * cos_theta;
    vec3f reflected_amt = shade(scene, reflect_ray, bounce + 1,
            max_bounces);

    // Final color
    return emittance + (brdf.cwiseProduct(reflected_amt));
}

int main(int argc, char* argv[])
{
    // Pathtracer settings
    int num_samples = 100; // Samples per pixel
    int num_bounces = 5; // Bounces per ray
    float fov = M_PI / 5.0; // Camera field of view

    // REMINDER: Make dimensions different to find bugs.
    int width = 256,
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
            vec3f eye(0, 1.0, 6.0); // ORIG z: 4
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
