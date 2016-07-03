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

vec3f Scene::shade(Ray ray, int bounce, int max_bounces)
{
    TriangleHit hit_data = m_tree->hit(ray);
    Triangle* tri = hit_data.tri;
    float dist = hit_data.dist;

    if (tri == NULL) {
        return vec3f(0.0, 0.0, 0.0);
    }

    tinyobj::mesh_t mesh = tri->shape_data->mesh;
    tinyobj::material_t mat = m_mats[mesh.material_ids[tri->index / 3]];

    // Return black if we've bounced around enough.
    if (bounce > max_bounces) {
        return vec3f(0.0, 0.0, 0.0);
    }

    // Material properties
    Ray reflect_ray;
    reflect_ray.pos = ray.pos + dist * ray.dir;
    vec3f emittance = to_vec3f(mat.emission);
    vec3f reflectance = to_vec3f(mat.diffuse);
    /* vec3f specular = to_vec3f(mat.specular); */
    vec3f &norm = tri->norm;

    // Reflect in a random direction on the normal's unit hemisphere.
    reflect_ray.dir = rand_hemisphere_vec(norm);

    // Calculate BRDF
    float cos_theta = norm.dot(-ray.dir);
    vec3f brdf = 2 * reflectance * cos_theta;
    vec3f reflected_amt = shade(reflect_ray, bounce + 1, max_bounces);

    // For specular, reflect perfectly.
    /* Ray spec_reflect_ray; */
    /* vec3f spec_reflected_amt; */
    /* if (specular.norm() != 0.0) { */
    /*     spec_reflect_ray.pos = reflect_ray.pos; */
    /*     spec_reflect_ray.dir = ray.dir + (2 * cos_theta * norm); */
    /*     spec_reflected_amt = shade(spec_reflect_ray, bounce + 1, */
    /*             max_bounces); */
    /* } */

    // Final color
    return emittance + brdf.cwiseProduct(reflected_amt);
    /* return emittance + brdf.cwiseProduct(reflected_amt + spec_reflected_amt); */
}

