#include "camera.hpp"
#include "ray.hpp"
#include "vector.hpp"

Camera::Camera(Ray view, vec3f up_dir)
{
    m_pos = view.pos;
    m_view = unit(view.dir);
    m_right = m_view.cross(unit(up_dir));
    m_up = m_right.cross(m_view);
};
