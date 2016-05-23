// See also:
// Metropolis light transport
// Volumetric Pathtracing

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <libgen.h>
#include <string.h>

#include "tiny_obj_loader.h"

bool load_scene(std::string model_path, std::string model_name)
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> mats;
    std::string err;

    bool success = tinyobj::LoadObj(shapes, mats, err, model_path.c_str(),
            model_name.c_str());

    std::cout << err << std::endl;
    return success;
}

int main(int argc, char* argv[])
{
    std::cout << "Pathtracer - Chris Laverdiere 2016" << std::endl;

    std::string model_path = "/home/chris/devel/graphics/models/CornellBox/";
    std::string model_name = "CornellBox-Original.obj";

    std::cout << "Loading model " << model_path << model_name << std::endl;

    bool model_load_success = load_scene(model_path, model_name);

    if (!model_load_success) {
        std::cerr << "Model failed to load, Exiting." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return 0;

}
