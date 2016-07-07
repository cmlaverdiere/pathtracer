#ifndef IMAGE_H
#define IMAGE_H

#include "vector.hpp"

void write_pixel(uint8_t* pixels, const vec3f &color, int x, int y, int width);
void write_png(const char* filename, uint8_t* pixel_data,
        int img_width, int img_height);

#endif
