#include "camera.hpp"
#include "ray.hpp"
#include "vector.hpp"

Camera::Camera(Ray view, vec3f up_dir) : m_view(view.dir)
{
    m_pos = view.pos;
    m_right = view.dir.cross(up_dir);
    m_up = m_right.cross(view.dir);
}
