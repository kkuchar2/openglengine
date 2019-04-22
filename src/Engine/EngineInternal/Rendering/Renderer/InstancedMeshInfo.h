#pragma once

#include <memory>
#include <Rendering/Mesh/Mesh.h>

class InstancedMeshInfo {
    public:
        std::shared_ptr<Mesh> mesh;
        int instanceCount = 0;

        InstancedMeshInfo(const std::shared_ptr<Mesh> & mesh, const int & instanceCount) {
            this->mesh = mesh;
            this->instanceCount = instanceCount;
        }

        void increment() {
            instanceCount++;
        }

        static std::shared_ptr<InstancedMeshInfo> ptr(const std::shared_ptr<Mesh> & mesh,
                const int & instanceCount) {
            return std::make_shared<InstancedMeshInfo>(mesh, instanceCount);
        }
};
