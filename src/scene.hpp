#ifndef SCENE_H
#define SCENE_H

#include <vector>

// TODO wrap tinyobj
#include "tiny_obj_loader.h"

#include "kdtree.hpp"

class Scene {
    public:
        std::vector<tinyobj::shape_t> m_shapes;
        std::vector<tinyobj::material_t> m_mats;
        KdTree* m_tree;

        Scene(std::string model_path, std::string model_name);
        vec3f shade(Ray ray, int bounce=0, int max_bounces=3);
};

#endif
