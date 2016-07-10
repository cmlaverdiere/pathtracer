#ifndef VECTOR_H
#define VECTOR_H

#include <eigen3/Eigen/Dense>

#include <vector>
#include <numeric>

typedef Eigen::Vector3f vec3f;
typedef Eigen::Vector3d vec3i;

vec3f to_vec3f(float* a);
vec3f unit(const vec3f &v);
vec3f vec_average(const std::vector<vec3f>& vecs);
vec3f rand_hemisphere_vec(const vec3f &norm);

inline vec3f to_vec3f(float* a)
{
    vec3f v(a[0], a[1], a[2]);
    return v;
}

inline vec3f unit(const vec3f &v)
{
    vec3f vn(v / v.norm());
    return vn;
}

inline vec3f vec_average(const std::vector<vec3f> &vecs)
{
    vec3f accum(0.0, 0.0, 0.0);
    accum = std::accumulate(vecs.begin(), vecs.end(), accum);
    return accum / vecs.size();
}

inline vec3f rand_hemisphere_vec(const vec3f &norm)
{
    vec3f randy = Eigen::Vector3f::Random();
    if (randy.dot(norm) < 0) {
        return -randy;
    } else {
        return randy;
    }
}

#endif
