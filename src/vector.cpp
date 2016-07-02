#include "vector.hpp"

// DES: wrap Eigen

vec3f to_vec3f(float* a)
{
    vec3f v(a[0], a[1], a[2]);
    return v;
}

vec3f unit(vec3f &v)
{
    vec3f vn(v / v.norm());
    return vn;
}

vec3f vec_average(std::vector<vec3f> vecs)
{
    vec3f accum(0.0, 0.0, 0.0);
    for (vec3f v : vecs) {
        accum += v;
    }
    return accum / vecs.size();
}

vec3f rand_hemisphere_vec(vec3f &norm)
{
    vec3f randy = Eigen::Vector3f::Random();
    if (randy.dot(norm) < 0) {
        randy = -randy;
    }
    return unit(randy);
}

