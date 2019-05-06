#include "NormalsGenerator.h"

#include <Engine/EngineInternal/Rendering/Mesh/TriangleInfo.h>

void NormalsGenerator::generate(Mesh * mesh) {
    std::map<unsigned int, std::vector<TriangleInfo>> vertexToTriangles;

    std::vector<TriangleInfo> triangles;

    auto vertices = mesh->vertices;

    for (unsigned int vertexId = 0; vertexId < vertices.size() / 3; vertexId++) {
        vertexToTriangles.insert(std::pair<int, std::vector<TriangleInfo>>(vertexId, triangles));
    }

    auto indices = mesh->indices;

    for (unsigned int j = 0; j < indices.size() / 3; j++) {
        unsigned int v1 = indices[j * 3];
        unsigned int v2 = indices[j * 3 + 1];
        unsigned int v3 = indices[j * 3 + 2];

        glm::vec3 v_1 = glm::vec3(vertices[v1 * 3], vertices[v1 * 3 + 1], vertices[v1 * 3 + 2]);
        glm::vec3 v_2 = glm::vec3(vertices[v2 * 3], vertices[v2 * 3 + 1], vertices[v2 * 3 + 2]);
        glm::vec3 v_3 = glm::vec3(vertices[v3 * 3], vertices[v3 * 3 + 1], vertices[v3 * 3 + 2]);

        glm::vec3 a = v_2 - v_1;
        glm::vec3 b = v_3 - v_1;

        TriangleInfo info{};
        info.angle = std::acos(dot(a, b) / (length(a) * length(b)));
        info.normal = normalize(cross(a, b));

        vertexToTriangles.at(v1).emplace_back(info);
        vertexToTriangles.at(v2).emplace_back(info);
        vertexToTriangles.at(v3).emplace_back(info);
    }

    for (auto & pair : vertexToTriangles) {

        std::vector<TriangleInfo> triangleInfos = pair.second;

        glm::vec3 weightedSum = glm::vec3(0.0, 0.0, 0.0);

        for (auto & info : triangleInfos) {
            weightedSum += info.normal * info.angle;
        }

        weightedSum /= triangleInfos.size();

        mesh->normals.insert(mesh->normals.end(), {weightedSum.x, weightedSum.y, weightedSum.z});
    }
}
