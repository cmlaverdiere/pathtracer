#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "kdtree.hpp"
#include "model.hpp"

struct Scene {
    std::vector<Shape> m_shapes;
    std::vector<Material> m_mats;
    KdTree* m_tree;

    Scene(std::string model_name);
};

#endif
