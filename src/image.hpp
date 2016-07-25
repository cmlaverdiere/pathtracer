#ifndef IMAGE_H
#define IMAGE_H

#include "vector.hpp"

void write_png(const char* filename, std::vector<vec3f> &pixel_data,
        int img_width, int img_height);

#endif
