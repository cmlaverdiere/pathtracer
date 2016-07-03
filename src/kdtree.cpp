#include <vector>

#include "kdtree.hpp"

// Naive BSP construction (midpoint)
// A tree is constructed with at most max_tris on each leaf.
// OPT: use SAH
// OPT: precalc midpoints
KdTree::KdTree(std::vector<Triangle> tris, int dim_split, int max_tris)
{
    // Leaf creation.
    if (tris.size() <= max_tris) {
        m_tris = tris; // PROFILE copy
        m_left = NULL;
        m_right = NULL;
        return;
    }

    // Internal node creation.

    // Precalculate min/max/average coordinate info.
    float midpoint_total = 0.0;
    float max_dims[3] = {0.0};
    float min_dims[3] = {INF};
    for (int i=0; i < tris.size(); i++) {
        for (int vert=0; vert < 3; vert++) {
            for (int dim=0; dim < 3; dim++) {
                float val = tris[i][vert][dim];
                if (max_dims[dim] < val) max_dims[dim] = val;
                if (min_dims[dim] > val) min_dims[dim] = val;
            }
        }
        midpoint_total += tris[i].midpoint()[dim_split];
    }

    // Find the average coordinate along dimension dim_split for left / right
    // tree separation.
    float dim_avg = midpoint_total / tris.size();

    // Use max / min dimensions for bounding box creation.
    vec3f lower_left = to_vec3f(min_dims);
    vec3f upper_right = to_vec3f(max_dims);
    m_box.ll = lower_left;
    m_box.ur = upper_right;

    // Split the tree at the midpoint and construct each half.
    std::vector<Triangle> left_tris, right_tris;
    for (int i=0; i < tris.size(); i++) {
        if (tris[i].midpoint()[dim_split] < dim_avg) {
            left_tris.push_back(tris[i]);
        } else {
            right_tris.push_back(tris[i]);
        }
    }

    int next_dim = (dim_split + 1) % 3;
    m_left = new KdTree(left_tris, next_dim);
    m_right = new KdTree(right_tris, next_dim);
}

TriangleHit KdTree::hit(Ray &ray)
{
    // At leaf
    if (m_left == NULL && m_right == NULL) {
        TriangleHit hit_data;
        float cl_dist = INF;
        Triangle *cl_tri = NULL;

        // Find which triangle (if any) our ray hits.
        bool hit = false;
        for (int t=0; t < m_tris.size(); t++) {
            Triangle &tri = m_tris[t];
            float dist = tri.intersect(ray);

            if (dist < cl_dist && dist != 0) {
                hit = true;
                cl_dist = dist;
                cl_tri = &(m_tris[t]);
            }
        }

        hit_data.tri = cl_tri;
        hit_data.dist = cl_dist;
        return hit_data;
    }

    // At interior node
    else if (m_box.intersect(ray)) {
        TriangleHit left_hit = m_left->hit(ray);
        TriangleHit right_hit = m_right->hit(ray);
        if (left_hit.tri == NULL) {
            return right_hit;
        } else {
            // We may hit triangles in both trees. In this case, take the
            // closer hit.
            if (left_hit.dist < right_hit.dist) {
                return left_hit;
            } else {
                return right_hit;
            }
        }
    }

    TriangleHit miss;
    return miss;
}
