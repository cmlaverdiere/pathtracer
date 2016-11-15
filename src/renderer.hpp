#ifndef RENDERER_H
#define RENDERER_H

#include "camera.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "vector.hpp"
#include "workqueue.hpp"

typedef struct {
    int image_width, image_height; // Image dimensions in pixels
    int num_samples; // Number of samples for each pixel
    int num_bounces; // Number of bounces for each ray
    int num_threads; // Number of threads to use for rendering.
    int bar_length; // Number of '.' to show in progress bar.
    float fov; // Field of view angle in radians
    vec3f cam_eye, cam_up, cam_at;
} RenderOpts;

class Renderer {

private:
    std::vector<vec3f> m_pixel_buf; // Internal buffer for RGB pixel data.
    std::vector<int> m_sample_counts; // How many times each pixel has been sampled.
    float m_frust_top, m_frust_bottom, m_frust_right, m_frust_left;

    WorkQueue m_pixel_queue; // Consumer queue to read next pixel from.
    std::vector<std::thread> m_workers; // Thread pool for parallel pixel rendering.
    Camera* m_camera;

    /* Cast a ray into the scene and return a color. */
    vec3f sample(Scene& scene, Ray ray, int bounce=0, int max_bounces=3);

public:
    RenderOpts m_render_opts;

    std::vector<vec3f>* get_pixels() { return &m_pixel_buf; }
    void start_render(Scene& scene);
    void work_render(Scene& scene);
    int get_num_pixels();
    void update_frustum_view();

    Renderer(RenderOpts render_opts);
};

#endif
