#pragma once

#include <Mesh/Mesh.h>
#include <Mesh/MeshRenderer/MeshRenderer.h>

class RenderInfo {
    public:

        /// Mesh that will be rendered
        std::shared_ptr<Mesh> mesh;

        /// Renderer of current mesh
        std::shared_ptr<MeshRenderer> renderer;

        /// Keep track of all game objects associated to current mesh
        std::vector<std::shared_ptr<GameObjectBase>> objects;

        RenderInfo(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & child, const std::shared_ptr<MeshRenderer> & meshRenderer) {
            this->mesh = mesh;
            this->renderer = meshRenderer;
            this->renderer->init(this->mesh);

            objects.push_back(child);
            child->transform.modelMatrixIndex = objects.size() - 1;
            child->transform.matricesRef = &mesh->modelMatrices;
            mesh->modelMatrices.push_back(child->transform.modelMatrix);
            mesh->colorVectors.push_back(meshRenderer->color);
        }


        void addInstance(const std::shared_ptr<GameObjectBase> & child, const glm::vec4 & color) {
            objects.push_back(child);
            child->transform.modelMatrixIndex = objects.size() - 1;
            child->transform.matricesRef = &mesh->modelMatrices;
            mesh->modelMatrices.push_back(child->transform.modelMatrix);
            mesh->colorVectors.push_back(color);
        }
};