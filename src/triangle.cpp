#include "triangle.hpp"
#include "ray.hpp"

vec3f& Triangle::operator[] (const int index)
{
    return verts[index];
}

vec3f Triangle::midpoint()
{
    return (verts[0] + verts[1] + verts[2]) / 3.0;
}

// https://en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
// OPT: precalculate dominant triangle axis.
float Triangle::intersect(const Ray &ray)
{
    float EPSILON = 0.0001;

    vec3f e1, e2;
    vec3f p, q, r;
    float det, inv_det, u, v;
    float t;

    e1 = verts[1] - verts[0];
    e2 = verts[2] - verts[0];

    p = ray.dir.cross(e2);
    det = e1.dot(p);

    if (det > -EPSILON && det < EPSILON) return 0;

    inv_det = 1.0 / det;
    r = ray.pos - verts[0];
    u = r.dot(p) * inv_det;

    if (u < 0.0 || u > 1.0) return 0;

    q = r.cross(e1);
    v = ray.dir.dot(q) * inv_det;

    if (v < 0.0 || u + v > 1.0) return 0;

    t = e2.dot(q) * inv_det;

    if (t > EPSILON) {
        return t;
    } else {
        return 0;
    }
}

