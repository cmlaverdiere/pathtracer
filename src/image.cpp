#include "png++/png.hpp"

#include "image.hpp"
#include "vector.hpp"

void write_png(const char* filename, std::vector<vec3f> &pixel_data,
        int img_width, int img_height)
{
    png::image<png::rgb_pixel> image(img_width, img_height);
    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for (png::uint_32 x = 0; x < image.get_width(); ++x) {
            int index = (y * image.get_width() + x);
            image.set_pixel(x, y, png::rgb_pixel(
                    (uint8_t) (255 * pixel_data[index].x()),
                    (uint8_t) (255 * pixel_data[index].y()),
                    (uint8_t) (255 * pixel_data[index].z())));
        }
    }
    image.write(filename);
}

