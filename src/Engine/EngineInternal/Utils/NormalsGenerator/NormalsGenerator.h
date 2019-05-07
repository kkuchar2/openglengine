#pragma once

#include <Rendering/Mesh/Mesh.h>

struct TriangleInfo {
    float angle;
    glm::vec3 normal;
};

class NormalsGenerator {
    public:
        static void generate(Mesh * mesh);
};