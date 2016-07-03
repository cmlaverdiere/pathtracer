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
    int index;

    vec3f& operator[] (const int index);
    vec3f midpoint();
    float intersect(Ray &ray);
} Triangle;

typedef struct {
    Triangle* tri = NULL;
    float dist = INF;
} TriangleHit;

#endif
