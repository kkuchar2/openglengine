#include "BoundingBoxGenerator.h"

void BoundingBoxGenerator::calculateBoundingBox(const std::shared_ptr<Mesh> & mesh,
                                                const std::shared_ptr<GameObject> & child) {
    float minFloat = std::numeric_limits<float>::min();
    float maxFloat = std::numeric_limits<float>::max();

    float minX = maxFloat;
    float minY = maxFloat;
    float minZ = maxFloat;

    float maxX = minFloat;
    float maxY = minFloat;
    float maxZ = minFloat;

    for (unsigned int vertexId = 0; vertexId < mesh->vertices.size() / 3; vertexId++) {
        glm::vec3 coords = glm::vec3(
                mesh->vertices[vertexId * 3],
                mesh->vertices[vertexId * 3 + 1],
                mesh->vertices[vertexId * 3 + 2]
        );

        if (coords.x > maxX) {
            maxX = coords.x;
        }

        if (coords.y > maxY) {
            maxY = coords.y;
        }

        if (coords.z > maxZ) {
            maxZ = coords.z;
        }

        if (coords.x < minX) {
            minX = coords.x;
        }

        if (coords.y < minY) {
            minY = coords.y;
        }

        if (coords.z < minZ) {
            minZ = coords.z;
        }
    }
    BoundingBox b{};

    b.size = glm::vec3(std::abs(maxX - minX), std::abs(maxY - minY), std::abs(maxZ - minZ));
    b.center = glm::vec3(minX + (maxX - minX) / 2.0f, minY + (maxY - minY) / 2.0f, minZ + (maxZ - minZ) / 2.0f);

    glm::vec3 max = glm::vec3(maxX, maxY, maxZ);
    glm::vec3 min = glm::vec3(minX, minY, minZ);


    std::shared_ptr<MeshComponent> cubeMeshProto = std::make_shared<MeshComponent>();
    cubeMeshProto->meshType = CUBE;
    cubeMeshProto->shaderType = AMBIENT;
    cubeMeshProto->color = glm::vec4(0.0, 1.0, 0.2f, 1.0f);

    child->bbox.center = b.center;
    child->bbox.size = b.size;
    child->boundingBox = std::make_shared<GameObject>();
    child->boundingBox->instanced = true;
    child->boundingBox->addComponent(cubeMeshProto);
}
