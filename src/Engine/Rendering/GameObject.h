#ifndef OPENGL_GAMEOBJECT_H
#define OPENGL_GAMEOBJECT_H

#include <memory>
#include <vector>
#include "../Window/Input/MessageListener.h"

class GameObject {

    public:
        std::string name = "Default";
        std::vector<std::shared_ptr<MessageListener>> components;

        GameObject() = default;

        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type* = nullptr>
        GameObject(std::shared_ptr<T> component) {
            addComponent(component);
        }


        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type* = nullptr>
        void addComponent(std::shared_ptr<T> component) {
            components.push_back(component);
        }

};

#endif //OPENGL_GAMEOBJECT_H