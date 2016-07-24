#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.hpp"
#include "kdtree.hpp"
#include "model.hpp"

// DES: Separate into Renderer class, move out of Scene.
typedef struct {
    int image_width, image_height; // Image dimensions in pixels
    int num_samples; // Number of samples for each pixel
    int num_bounces; // Number of bounces for each ray
    float fov; // Field of view angle in radians

    /*
     * Number of threads to use for rendering on each dimension. For instance,
     * with x=4 and y=3, the image will be split into a 4x3 grid, with 12
     * threads rendering the image.
     */
    int x_threads, y_threads;
} RenderOpts;

class Scene {
    private:
        std::vector<Shape> m_shapes;
        std::vector<Material> m_mats;
        KdTree* m_tree;
        RenderOpts m_render_opts;
        Camera m_camera;

        /* Sample the pixel intersected by ray with num_samples samples. */
        std::vector<vec3f> sample(const Ray &ray, int num_samples,
                int num_bounces);

        /* Cast a ray into the scene and return a color. */
        vec3f shade(Ray ray, int bounce=0, int max_bounces=3);

        /*
         * Renders a block of the image with upper left at (startx, starty) and
         * lower right at (startx + lenx, starty + leny).
         */
        void render_block(uint8_t *pixels, int startx, int starty,
                int lenx, int leny);

    public:
        Scene(std::string model_name, RenderOpts render_opts, Camera camera);
        void render(std::string outfile_path);
};

#endif
