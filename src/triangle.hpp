#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "model.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vector.hpp"

// REF: move shape_data / index to shader
typedef struct {
    vec3f verts[3];
    vec3f norm;
    Shape *shape_data;
    size_t index;

    vec3f& operator[] (const int index);
    vec3f midpoint();
    float intersect(const Ray &ray);
} Triangle;

typedef struct {
    Triangle* tri = nullptr;
    float dist = INF;
} TriangleHit;

#endif
