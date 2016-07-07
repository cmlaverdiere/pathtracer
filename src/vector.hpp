#ifndef VECTOR_H
#define VECTOR_H

#include <eigen3/Eigen/Dense>

#include <vector>

typedef Eigen::Vector3f vec3f;
typedef Eigen::Vector3d vec3i;

vec3f to_vec3f(float* a);
vec3f unit(const vec3f &v);
vec3f vec_average(const std::vector<vec3f>& vecs);
vec3f rand_hemisphere_vec(const vec3f &norm);

#endif
