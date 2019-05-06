#pragma once

#include <memory>
#include <vector>
#include <Components/Component.h>
#include <Components/MeshComponent/MeshComponent.h>
#include <Engine/EngineInternal/Rendering/Projection.h>
#include <Rendering/Mesh/Mesh.h>
#include <Engine/EngineInternal/Rendering/Mesh/BoundingBox.h>
#include "Engine/EngineInternal/Scene/Transform.h"

class GameObject {

    public:

        bool instanced = false;

        Transform transform;

        int rb_idx;

        std::shared_ptr<GameObject> boundingBox;

        BoundingBox bbox;

        std::vector<std::shared_ptr<Component>> components;

        std::vector<std::shared_ptr<GameObject>> children;

        std::shared_ptr<MeshComponent> meshProto;

        Projection projection = PERSPECTIVE;

        GameObject();

        explicit GameObject(const std::shared_ptr<Component> & baseComponent);

        void addComponent(const std::shared_ptr<Component> & baseComponent);

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for (auto & component : components) {

                auto c = std::dynamic_pointer_cast<T>(component);

                if (c) {
                    return c;
                }
            }

            return nullptr;
        }


        template<typename T>
        std::shared_ptr<T> castComponent(const std::shared_ptr<Component> & component) {
            std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component);

            if (t) {
                return t;
            }

            return nullptr;
        }

        void init();

        void Update();

        static std::shared_ptr<GameObject> create(
            const glm::vec3 & position = glm::vec3(0.0f),
            const glm::vec3 & rotation = glm::vec3(0.0f),
            const glm::vec3 & scale = glm::vec3(1.0f)
        );
};