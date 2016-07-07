#include "aabb.hpp"
#include "utils.hpp"

// Modified slabs method from Real Time Rendering ch 16.7.1
// PROFILE: Branch all at once.
// OPT: Try without div by f.
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

        if (t1 > t_min) t_min = t1;
        if (t2 < t_max) t_max = t2;
        if (t_min > t_max) return false;
        if (t_max < 0) return false;
    }

    return true;
}

