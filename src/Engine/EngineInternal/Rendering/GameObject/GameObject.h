#pragma once

#include <memory>
#include <vector>

#include "Mesh/Mesh.h"
#include "Primitives/Cube.h"
#include "Shading/ShaderPool.h"
#include "Primitives/Line.h"
#include "Mesh/MeshType.h"

struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

class GameObject {

    public:
        Transform transform;

        bool drawBoundingBox = false;

        std::string name = "Default";
        std::vector<std::shared_ptr<Component>> components;

        GameObject() = default;

        GameObject(const std::shared_ptr<Component> & component);

        void addComponent(const std::shared_ptr<Component> & component);

        std::vector<std::shared_ptr<GameObject>> createBoundingBox();

        static std::vector<std::shared_ptr<GameObject>> createBoundingBoxLines(BoundingBox boundingBox);
        static std::shared_ptr<GameObject> createLineObject(glm::vec3 start, glm::vec3 end, BoundingBox & boundingBox);
        static std::shared_ptr<Line> createLine(glm::vec3 start, glm::vec3 end, glm::vec3 rotation, glm::vec3 position);

        static std::shared_ptr<GameObject> create(const std::shared_ptr<Component> & component);

        static std::shared_ptr<GameObject> create();

        void prepare();

        std::shared_ptr<Mesh> getMesh();

        MeshType getMeshType();

        BoundingBox calculateBoundingBox();
};