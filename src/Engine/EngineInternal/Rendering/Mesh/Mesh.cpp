#include "Mesh/Mesh.h"

#include <Utils/NormalsGenerator/NormalsGenerator.h>

Mesh::Mesh(const std::string & path) {
    loadFromResource(path);
}

Mesh::Mesh() {}

void Mesh::loadFromResource(const std::string & path) {

    std::cout << "Loading: " << path << std::endl;

    tinyobj::attrib_t attrib;

    std::string warning;
    std::string error;

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, path.c_str());

    if (!ret) {
        if (!error.empty()) {
            std::cerr << "Error: " << error << std::endl;
        }
    }

    if (!warning.empty()) {
        std::cout << "Mesh: " << warning << std::endl;
    }

    vertices = attrib.vertices;

    for (const auto & shape : shapes) {
        for (const auto & index : shape.mesh.indices) {
            indices.push_back((unsigned int) index.vertex_index);
        }
    }
}

std::shared_ptr<Mesh> Mesh::create(const char * path) {
    return std::make_shared<Mesh>(path);
}