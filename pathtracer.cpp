// See also:
// Metropolis light transport
// Volumetric Pathtracing
//
// Requires: tinyobjloader (included), Eigen, png++

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <libgen.h>
#include <string.h>

#include "tiny_obj_loader.h"
#include "png++/png.hpp"
#include <eigen3/Eigen/Dense>

void write_png(const char* filename, int ***pixel_data,
        int img_width, int img_height)
{
    png::image<png::rgb_pixel> image(img_width, img_height);
    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for (png::uint_32 x = 0; x < image.get_width(); ++x) {
            image[y][x] = png::rgb_pixel(
                    pixel_data[y][x][0],
                    pixel_data[y][x][1],
                    pixel_data[y][x][2]);
        }
    }
    image.write(filename);
}

void load_scene(std::vector<tinyobj::shape_t> &shapes,
        std::vector<tinyobj::material_t> &mats,
        std::string model_path, std::string model_name)
{
    std::string err;

    std::string obj_filename = model_path + model_name;
    bool success = tinyobj::LoadObj(shapes, mats, err, obj_filename.c_str(),
            model_path.c_str());

    if (!success) {
        std::cout << err << std::endl;
        std::cerr << "Model failed to load, Exiting." << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::cout << "Model loaded successfully." << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> mats;

    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    std::string model_path = "/home/chris/devel/graphics/models/CornellBox/";
    std::string model_name = "CornellBox-Original.obj";

    std::cout << "Loading model " << model_path << model_name << std::endl;
    load_scene(shapes, mats, model_path, model_name);

    std::cout << "Loaded " << shapes.size() << " shapes:" << std::endl;
    for (tinyobj::shape_t shape : shapes) {
        std::cout << shape.name << std::endl;
    }

    return 0;
}
