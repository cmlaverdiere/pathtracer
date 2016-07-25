#include <algorithm>
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <libgen.h>
#include <time.h>
#include <vector>

#include "image.hpp"
#include "model.hpp"
#include "scene.hpp"

Scene::Scene(std::string model_name, RenderOpts render_opts, Camera camera)
    : m_render_opts(render_opts), m_camera(camera)
{
    std::string err;

    std::cout << "Loading model " << model_name << std::endl;
    unsigned int flags =
        tinyobj::triangulation | tinyobj::calculate_normals;

    std::string model_name_copy(model_name);
    char* model_name_char = const_cast<char*>(model_name_copy.c_str());
    char* obj_dir = dirname(model_name_char);
    strcat(obj_dir, "/");

    bool success = tinyobj::LoadObj(m_shapes, m_mats, err,
            model_name.c_str(), obj_dir, flags);

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
        Shape shape = m_shapes[s];
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

vec3f Scene::shade(Ray ray, int bounce, int max_bounces)
{
    TriangleHit hit_data = m_tree->hit(ray);
    Triangle* tri = hit_data.tri;
    float dist = hit_data.dist;

    if (tri == nullptr) {
        return vec3f(0.0, 0.0, 0.0);
    }

    tinyobj::mesh_t mesh = tri->shape_data->mesh;
    Material mat = m_mats[mesh.material_ids[tri->index / 3]];

    // Return black if we've bounced around enough.
    if (bounce > max_bounces) {
        return vec3f(0.0, 0.0, 0.0);
    }

    // Material properties
    Ray reflect_ray;
    reflect_ray.pos = ray.pos + dist * ray.dir;
    vec3f emittance = to_vec3f(mat.emission);
    vec3f reflectance = to_vec3f(mat.diffuse);
    // vec3f specular = to_vec3f(mat.specular);
    vec3f &norm = tri->norm;

    // Reflect in a random direction on the normal's unit hemisphere.
    reflect_ray.dir = rand_hemisphere_vec(norm);

    // Calculate BRDF
    float cos_theta = norm.dot(-ray.dir);
    vec3f brdf = 2 * reflectance * cos_theta;
    vec3f reflected_amt = shade(reflect_ray, bounce + 1, max_bounces);

    // For specular, reflect perfectly.
    Ray spec_reflect_ray;
    vec3f spec_reflected_amt;
    spec_reflect_ray.pos = reflect_ray.pos;
    spec_reflect_ray.dir = ray.dir + (2 * cos_theta * norm);
    spec_reflected_amt = shade(spec_reflect_ray, bounce + 1,
            max_bounces);

    // Final color
    return emittance + brdf.cwiseProduct(reflected_amt + spec_reflected_amt);
}

void Scene::render(std::string outfile_path)
{
    int num_pixels = m_render_opts.image_height * m_render_opts.image_width;

    // For timing how long the rendering takes.
    auto start = std::chrono::steady_clock::now();

    /* Container for pixel color data. */
    std::vector<vec3f> pixels(num_pixels);

    /* How many times each pixel has been sampled. */
    int sample_counts[num_pixels];
    std::fill_n(sample_counts, num_pixels, 0);

    WorkQueue pixel_queue;

    // TODO randomize queue
    for (int i=0; i < num_pixels; i++) {
        pixel_queue.push_back(i);
    }

    // Seed for places we need random vector directions.
    srand(time(NULL));

    std::cout << "{" << std::flush;

    std::vector<std::thread> threads;
    for (int i=0; i < m_render_opts.num_threads; i++) {
        threads.push_back(
                std::thread(&Scene::render_pixel, this, std::ref(pixel_queue),
                    std::ref(pixels), &sample_counts[0]));
    }

    for (std::thread &t : threads){
        t.join();
    }

    std::cout << "}" << std::endl;

    std::cout << "Saving image to " << outfile_path << std::endl;
    write_png(outfile_path.c_str(), pixels, m_render_opts.image_width,
            m_render_opts.image_height);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Traced image in " <<
        (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0)
        << " seconds." << std::endl;
}

// TODO rename to render_pixels
void Scene::render_pixel(WorkQueue &pixel_queue, std::vector<vec3f> &pixels,
        int *sample_counts)
{
    // Top, bottom, left, right locations of frustum plane.
    const float t = tan(m_render_opts.fov / 2),
          b = -t,
          l = -t,
          r = t;

    const int total_needed = m_render_opts.image_width
        * m_render_opts.image_height
        * m_render_opts.num_samples;

    int pixels_done = 0;
    while (pixel_queue.size() != 0) { // TODO Or hit num_samples
        int pixel = pixel_queue.pop_front();

        int x = pixel % m_render_opts.image_width;
        int y = pixel / m_render_opts.image_height;

        float u = l + ((r - l) * (x + 0.5) / m_render_opts.image_height);
        float v = b + ((t - b) * (y + 0.5) / m_render_opts.image_width);
        v = -v;

        vec3f dir = (u * m_camera.m_right)
            + (v * m_camera.m_up)
            + m_camera.m_view;

        Ray ray = { m_camera.m_pos, unit(dir) };

        vec3f sample = shade(ray, 0, m_render_opts.num_bounces);
        vec3f prev_sample = pixels[pixel];

        int sample_count = sample_counts[pixel];
        pixels[pixel] = (sample + (prev_sample * sample_count)) / (sample_count + 1);
        sample_counts[pixel] += 1;

        if (sample_counts[pixel] >= m_render_opts.num_samples) {
            return;
        }

        pixels_done++;
        if (pixels_done % (total_needed / m_render_opts.bar_length) == 0) {
            std::cout << "." << std::flush;
        }

        pixel_queue.push_back(pixel);
    }
}
