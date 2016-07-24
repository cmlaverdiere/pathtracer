#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include "vector.hpp"

class Camera {
    public:
        vec3f m_view, m_up, m_right;
        vec3f m_pos;

        Camera(Ray view, vec3f up);
};

#endif
