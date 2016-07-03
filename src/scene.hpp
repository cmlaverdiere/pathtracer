#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "kdtree.hpp"
#include "model.hpp"

class Scene {
    public:
        std::vector<Shape> m_shapes;
        std::vector<Material> m_mats;
        KdTree* m_tree;

        Scene(std::string model_path, std::string model_name);
        vec3f shade(Ray ray, int bounce=0, int max_bounces=3);
};

#endif
