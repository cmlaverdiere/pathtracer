#include "aabb.hpp"
#include "utils.hpp"

#include <algorithm>

// Modified slabs method from Real Time Rendering ch 16.7.1
bool Box::intersect(const Ray &ray)
{
    float t_min = -INF;
    float t_max = INF;

    vec3f to_p1 = ll - ray.pos;
    vec3f to_p2 = ur - ray.pos;

    // TODO extra checks.
    for (int i=0; i<3; i++) {
        float f = ray.dir[i];
        float t1 = to_p1[i] / f;
        float t2 = to_p2[i] / f;

        if (t1 > t2) {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        t_min = std::max(t1, t_min);
        t_max = std::min(t2, t_max);
        if (t_min > t_max) return false;
        if (t_max < 0) return false;
    }

    return true;
}

