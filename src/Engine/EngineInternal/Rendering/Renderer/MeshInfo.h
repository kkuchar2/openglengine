#pragma once

#include <memory>
#include <Rendering/Mesh/Mesh.h>
#include <glfw/deps/linmath.h>
#include <Rendering/Mesh/MeshBuilder.h>

class MeshInfo {
    public:
        std::shared_ptr<Mesh> mesh;
        std::vector<std::shared_ptr<GameObject>> objects;

        MeshInfo(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObject> & o) {
            this->mesh = mesh;
            objects.push_back(o);
        }

        void addInstance(const std::shared_ptr<GameObject> & o, const glm::vec4 & color) {
            objects.push_back(o);
            mesh->modelMatrices.push_back(o->transform.modelMatrix);
            mesh->colorVectors.push_back(color);
        }

        void Update() {
            int i = 0;
            for (auto & obj : objects) {
                obj->OnUpdate();
                mesh->modelMatrices[i] = obj->transform.modelMatrix;
                i++;
            }

        }

        static std::shared_ptr<MeshInfo> ptr(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObject> & o) {
            return std::make_shared<MeshInfo>(mesh, o);
        }
};