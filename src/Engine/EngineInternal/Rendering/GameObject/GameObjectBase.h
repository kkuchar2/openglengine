#pragma once

#include <memory>
#include <vector>
#include <Component.h>
#include <Rendering/Mesh/MeshPrototype.h>
#include <Rendering/Camera/Projection.h>
#include <Rendering/Mesh/Mesh.h>
#include "Transform.h"

class GameObjectBase {

    public:

        Transform transform;

        std::shared_ptr<GameObjectBase> boundingBox;

        BoundingBox bbox;

        std::vector<std::shared_ptr<Component>> components;

        std::vector<std::shared_ptr<GameObjectBase>> children;

        std::shared_ptr<MeshPrototype> meshProto;

        Projection projection = PERSPECTIVE;

        GameObjectBase();

        explicit GameObjectBase(const std::shared_ptr<Component> & component);

        void addComponent(const std::shared_ptr<Component> & component);

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
        static std::shared_ptr<T> castComponent(const std::shared_ptr<Component> & component) {
            std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component);

            if (t) {
                return t;
            }

            return nullptr;
        }

        void Update() {
            for (auto & component : components) {
                component->Update();
            }

            if (boundingBox.get()) {
                boundingBox->transform.position = transform.position;
                boundingBox->transform.pivot = transform.scale * bbox.center;
                boundingBox->transform.rotation = transform.rotation;
                boundingBox->transform.scale = transform.scale * bbox.size;

                boundingBox->transform.positionMatrix = MatrixUtils::translationMatrix(boundingBox->transform.position);
                boundingBox->transform.scaleMatrix = MatrixUtils::scaleMatrix(boundingBox->transform.scale);
                boundingBox->transform.rotationMatrix = MatrixUtils::rotationMatrix(boundingBox->transform.rotation);
            }
        }
};