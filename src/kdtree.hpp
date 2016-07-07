#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

#include "aabb.hpp"
#include "triangle.hpp"

class KdTree {
    private:
        Box m_box;
        KdTree *m_left, *m_right;
        std::vector<Triangle> m_tris;

    public:
        KdTree(std::vector<Triangle> &tris, int dim_split = 0,
                int max_tris = 3);
        TriangleHit hit(const Ray &ray);
};

#endif
