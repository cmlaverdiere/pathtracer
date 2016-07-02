#ifndef AABB_H
#define AABB_H

#include "vector.hpp"
#include "ray.hpp"

// Axis aligned bounding box (AABB)
class Box {
    public:
        vec3f ll, ur;
        bool intersect(Ray &ray);
};

#endif
