#include <algorithm>
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <libgen.h>
#include <thread>
#include <time.h>
#include <vector>

#include "image.hpp"
#include "model.hpp"
#include "ray.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "vector.hpp"
#include "workqueue.hpp"

// DES: Separate renderer class from rendering instance.

Renderer::Renderer(RenderOpts render_opts) : m_render_opts(render_opts) {
    Ray look_at = { render_opts.cam_eye, render_opts.cam_at };
    m_camera = new Camera(look_at, render_opts.cam_up);

    m_pixels_done = 0;

    int num_pixels = get_num_pixels();
    for (int i=0; i < num_pixels; i++) {
        vec3f empty_vec(0.0, 0.0, 0.0);
        m_pixel_buf.push_back(empty_vec);
        m_sample_counts.push_back(0);
    }

    update_frustum_view();

    // Populate pixel queue with a random ordering of pixels.
    std::vector<int> range(num_pixels);
    std::iota(range.begin(), range.end(), 0);
    std::random_shuffle(range.begin(), range.end());
    for (int i=0; i < num_pixels; i++) {
        m_pixel_queue.push_back(range[i]);
    }

    // Seed for places we need random vector directions.
    srand(time(NULL));
};

void Renderer::start_render(Scene& scene) {
    m_render_running = true;
    for (int t=0; t < m_render_opts.num_threads; t++) {
        m_workers.push_back(std::thread(&Renderer::work_render, this,
                                        std::ref(scene)));
    }
}

void Renderer::stop_render(bool wait=false) {
    m_render_running = false;
    if (wait) {
        for (std::thread &t : m_workers) {
            t.join();
        }
    }
}

int Renderer::get_num_pixels() {
    return m_render_opts.image_height * m_render_opts.image_width;
}

vec3f Renderer::sample(Scene& scene, Ray ray, int num_bounces)
{
    vec3f accum_radiance(0.0, 0.0, 0.0);
    vec3f rem_radiance(1.0, 1.0, 1.0);

    for (int b=0; b < num_bounces; b++) {
        TriangleHit hit_data = scene.m_tree->hit(ray);
        Triangle* tri = hit_data.tri;
        float dist = hit_data.dist;

        if (tri == nullptr) {
            return vec3f(0.0, 0.0, 0.0);
        }

        tinyobj::mesh_t mesh = tri->shape_data->mesh;
        Material mat = scene.m_mats[mesh.material_ids[tri->index / 3]];

        // Material properties
        vec3f emittance = to_vec3f(mat.emission);
        vec3f diffuse = to_vec3f(mat.diffuse);
        // vec3f specular = to_vec3f(mat.specular);
        vec3f &norm = tri->norm;

        // Calculate BRDF
        vec3f brdf = 2 * diffuse;

        // Reflect in a random direction on the normal's unit hemisphere.
        ray.pos = ray.pos + dist * ray.dir;
        // ray.dir = rand_hemisphere_vec(norm);
        ray.dir = cos_dist_hemisphere_vec(norm);

        // Add accumulation of outgoing radiance.
        accum_radiance += rem_radiance.cwiseProduct(emittance);
        rem_radiance = rem_radiance.cwiseProduct(brdf);

        // For specular, reflect perfectly.
        // Ray spec_reflect_ray;
        // vec3f spec_reflected_amt;
        // spec_reflect_ray.pos = reflect_ray.pos;
        // spec_reflect_ray.dir = ray.dir + (2 * cos_theta * norm);
        // spec_reflected_amt = sample(scene, spec_reflect_ray, bounce + 1,
        //         max_bounces);
    }

    return accum_radiance;
}

// OPT: precompute / store ray directions for x, y.
void Renderer::work_render(Scene &scene) {
    while (m_render_running) {
        int pixel_id = m_pixel_queue.pop_front();

        int x = pixel_id % m_render_opts.image_width;
        int y = pixel_id / m_render_opts.image_height;

        float u = m_frust_left + ((m_frust_right - m_frust_left)
                                  * (x + 0.5) / m_render_opts.image_height);
        float v = m_frust_bottom + ((m_frust_top - m_frust_bottom)
                                    * (y + 0.5) / m_render_opts.image_width);
        v = -v;

        vec3f dir = (u * m_camera->m_right) + (v * m_camera->m_up) + m_camera->m_view;
        Ray ray = { m_camera->m_pos, unit(dir) };

        vec3f new_sample = sample(scene, ray, m_render_opts.num_bounces);
        vec3f prev_sample = m_pixel_buf[pixel_id];

        int sample_count = m_sample_counts[pixel_id];
        m_pixel_buf[pixel_id] = (new_sample + (prev_sample * sample_count)) / (sample_count + 1);
        m_sample_counts[pixel_id] += 1;

        m_pixel_queue.push_back(pixel_id);
        m_pixels_done++;
    }
}

void Renderer::update_frustum_view() {
    m_frust_top = tan(m_render_opts.fov / 2);
    m_frust_bottom = -m_frust_top;
    m_frust_left = -m_frust_top;
    m_frust_right = m_frust_top;
}
