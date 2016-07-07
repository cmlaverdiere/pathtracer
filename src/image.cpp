#include "image.hpp"
#include "vector.hpp"

#include "png++/png.hpp"

void write_pixel(uint8_t* pixels, const vec3f &color, int x, int y, int width)
{
    // assert(color.x() <= 1.0 && color.y() <= 1.0 && color.z() <= 1.0);
    pixels[3 * (y * width + x)] = 255 * color.x();
    pixels[3 * (y * width + x) + 1] = 255 * color.y();
    pixels[3 * (y * width + x) + 2] = 255 * color.z();
}

void write_png(const char* filename, uint8_t* pixel_data,
        int img_width, int img_height)
{
    png::image<png::rgb_pixel> image(img_width, img_height);
    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for (png::uint_32 x = 0; x < image.get_width(); ++x) {
            image.set_pixel(x, y, png::rgb_pixel(
                    pixel_data[3 * (y * image.get_width() + x)],
                    pixel_data[3 * (y * image.get_width() + x) + 1],
                    pixel_data[3 * (y * image.get_width() + x) + 2]));
        }
    }
    image.write(filename);
}

