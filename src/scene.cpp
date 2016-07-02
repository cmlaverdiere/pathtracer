#include <iostream>

#include "tiny_obj_loader.h"

#include "scene.hpp"

// TODO make model class, own file.

Scene::Scene(std::string model_path, std::string model_name)
{
    std::string err;

    std::cout << "Loading model " << model_path << model_name << std::endl;
    unsigned int flags =
        tinyobj::triangulation | tinyobj::calculate_normals;

    std::string obj_filename = model_path + model_name;
    bool success = tinyobj::LoadObj(m_shapes, m_mats, err,
            obj_filename.c_str(), model_path.c_str(), flags);

    if (!success) {
        std::cout << err << std::endl;
        std::cerr << "Model failed to load, Exiting." << std::endl;
        std::exit(EXIT_FAILURE);
    } else {
        std::cout << "Model loaded successfully." << std::endl;
    }

    std::cout << "Constructing triangles" << std::endl;
    std::vector<Triangle> tris;
    for (int s=0; s < m_shapes.size(); s++) {
        tinyobj::shape_t shape = m_shapes[s];
        tinyobj::mesh_t mesh = shape.mesh;
        for (int i=0; i < mesh.indices.size(); i += 3) {
            unsigned int j1 = mesh.indices[i]*3;
            unsigned int j2 = mesh.indices[i+1]*3;
            unsigned int j3 = mesh.indices[i+2]*3;
            vec3f v1 = to_vec3f(&mesh.positions[j1]);
            vec3f v2 = to_vec3f(&mesh.positions[j2]);
            vec3f v3 = to_vec3f(&mesh.positions[j3]);
            vec3f norm = to_vec3f(&mesh.normals[j1]);

            Triangle tri = {
                .verts[0] = v1,
                .verts[1] = v2,
                .verts[2] = v3,
                .norm = norm,
                .shape_data = &(m_shapes[s]),
                .index = i
            };

            tris.push_back(tri);
        }
    }

    std::cout << "Constructing KdTree" << std::endl;
    m_tree = new KdTree(tris);
}

