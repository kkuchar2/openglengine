#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Engine/EngineInternal/Components/Component.h>
#include <Rendering/BoundingBox.h>
#include "Scene/Transform.h"

class GameObjectBase {

    protected:

        std::vector<std::shared_ptr<Component>> components;

    public:
        bool culled = false;

        Transform transform;

        BoundingBox bbox;

        std::shared_ptr<GameObjectBase> boundingBox;

        std::shared_ptr<Component> addComponent(const std::shared_ptr<Component> & baseComponent);

        template<typename T>
        bool hasComponent() {
            for (auto & component : components) {

                auto c = getComponent<T>();

                if (c.get()) {
                    return true;
                }
            }

            return false;
        }

        template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
        std::shared_ptr<T> getComponent() {
            for (auto & component : components) {

                auto c = std::dynamic_pointer_cast<T>(component);

                if (c.get()) {
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


        virtual void update(const bool & refreshMatrices) = 0;
        virtual void update(const Transform & t, const BoundingBox & bb, const bool & refreshMatrices) {}
};