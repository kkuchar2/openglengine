#pragma once

#include <memory>
#include <Rendering/Mesh/Mesh.h>
#include <glfw/deps/linmath.h>

class InstancedMeshInfo {
    public:
        std::shared_ptr<Mesh> mesh;
        int instanceCount = 0;

        InstancedMeshInfo(const std::shared_ptr<Mesh> & mesh, const int & instanceCount) {
            this->mesh = mesh;
            this->instanceCount = instanceCount;
        }

        void addInstance(const glm::mat4x4 & modelMatrix) {
            mesh->modelMatrices.push_back(modelMatrix);
            instanceCount++;
        }

        static std::shared_ptr<InstancedMeshInfo> ptr(const std::shared_ptr<Mesh> & mesh,
                const int & instanceCount) {
            return std::make_shared<InstancedMeshInfo>(mesh, instanceCount);
        }
};
