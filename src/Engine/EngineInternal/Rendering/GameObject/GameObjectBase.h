#pragma once

#include <memory>
#include <vector>
#include <Component.h>


class GameObjectBase {

    public:

        std::vector<std::shared_ptr<Component>> components;

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

        void OnUpdate() {
            for (auto & component : components) {
                component->Update();
            }
        }
};