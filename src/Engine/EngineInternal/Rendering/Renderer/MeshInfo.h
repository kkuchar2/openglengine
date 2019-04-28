#pragma once

#include <memory>
#include <Rendering/Mesh/Mesh.h>
#include <glfw/deps/linmath.h>
#include <Rendering/Mesh/MeshBuilder.h>
#include <Utils/BoundingBoxGenerator.h>

class MeshInfo {
    public:
        std::shared_ptr<Mesh> mesh;
        std::vector<std::shared_ptr<GameObjectBase>> objects;
        std::vector<std::shared_ptr<GameObjectBase>> boundingBoxes;

        MeshInfo(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & o) {
            this->mesh = mesh;
            objects.push_back(o);
            o->transform.index = objects.size() - 1;
            o->transform.matricesRef = &mesh->modelMatrices;
            mesh->modelMatrices.push_back(o->transform.modelMatrix);
        }

        void addInstance(const std::shared_ptr<GameObjectBase> & o, const glm::vec4 & color) {
            objects.push_back(o);
            o->transform.index = objects.size() - 1;
            o->transform.matricesRef = &mesh->modelMatrices;
            mesh->modelMatrices.push_back(o->transform.modelMatrix);
            mesh->colorVectors.push_back(color);
        }

        static std::shared_ptr<MeshInfo> ptr(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & o) {
            return std::make_shared<MeshInfo>(mesh, o);
        }
};