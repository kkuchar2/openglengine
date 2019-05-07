#pragma once

#include <memory>
#include <vector>
#include <Components/Component.h>
#include <Components/MeshComponent/MeshComponent.h>
#include <Engine/EngineInternal/Rendering/Projection.h>
#include <Rendering/Mesh/Mesh.h>
#include <Engine/EngineInternal/Rendering/BoundingBox.h>
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

        Projection projection = PERSPECTIVE;

        GameObject();

        explicit GameObject(const std::shared_ptr<Component> & baseComponent);

        void init();

        void update();

        std::shared_ptr<Component> addComponent(const std::shared_ptr<Component> & baseComponent);

        template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
        std::shared_ptr<T> getComponent() {
            for (auto & component : components) {

                auto c = std::dynamic_pointer_cast<T>(component);

                if (c) {
                    return c;
                }
            }

            return nullptr;
        }

        template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
        std::shared_ptr<T> getComponentOrDefault() {
            auto component = getComponent<T>();

            if (!component.get()) {
                return castComponent<T>(addComponent(std::make_shared<T>()));
            }

            return component;
        }

        template<typename T>
        std::shared_ptr<T> castComponent(const std::shared_ptr<Component> & component) {
            std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component);

            if (t) {
                return t;
            }

            return nullptr;
        }

        static std::shared_ptr<GameObject> create(
            const glm::vec3 & position = glm::vec3(0.0f),
            const glm::vec3 & rotation = glm::vec3(0.0f),
            const glm::vec3 & scale = glm::vec3(1.0f)
        );
};