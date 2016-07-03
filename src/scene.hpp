#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "kdtree.hpp"
#include "model.hpp"

typedef struct {
    int image_width, image_height; // Image dimensions in pixels
    int num_samples; // Number of samples for each pixel
    int num_bounces; // Number of bounces for each ray
    float fov; // Field of view angle in radians

    /* Number of threads to use for rendering on each dimension. For instance,
     * with x=4 and y=3, the image will be split into a 4x3 grid, with 12
     * threads rendering the image.
     */
    int x_threads, y_threads;
} RenderOpts;

class Scene {
    public:
        std::vector<Shape> m_shapes;
        std::vector<Material> m_mats;
        KdTree* m_tree;

        Scene(std::string model_path, std::string model_name);
        vec3f shade(Ray ray, int bounce=0, int max_bounces=3);
        void render(RenderOpts &opts, std::string outfile_path);
};

#endif
