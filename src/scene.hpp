#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.hpp"
#include "kdtree.hpp"
#include "model.hpp"
#include "workqueue.hpp"

// DES: Separate into Renderer class, move out of Scene.
typedef struct {
    int image_width, image_height; // Image dimensions in pixels
    int num_samples; // Number of samples for each pixel
    int num_bounces; // Number of bounces for each ray
    int num_threads; // Number of threads to use for rendering.
    int bar_length; // Number of '.' to show in progress bar.
    float fov; // Field of view angle in radians
} RenderOpts;

class Scene {
    private:
        std::vector<Shape> m_shapes;
        std::vector<Material> m_mats;
        KdTree* m_tree;
        RenderOpts m_render_opts;
        Camera m_camera;

        /* Cast a ray into the scene and return a color. */
        vec3f shade(Ray ray, int bounce=0, int max_bounces=3);

        /* Renders a single pixel of the image at (pixel_x, pixel_y) */
        void render_pixel(WorkQueue &pixel_queue, std::vector<vec3f> &pixels,
                int *sample_counts);

    public:
        Scene(std::string model_name, RenderOpts render_opts, Camera camera);
        void render(std::string outfile_path);
};

#endif
