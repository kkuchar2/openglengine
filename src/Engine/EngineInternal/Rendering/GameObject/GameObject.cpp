#include "GameObject.h"
#include "../../Behaviour/BehaviourComponent.h"

GameObject::GameObject(const std::shared_ptr<Component> & component) : GameObjectBase(component) {
}

std::shared_ptr<GameObject> GameObject::create() {
    return std::make_shared<GameObject>();
}

std::shared_ptr<GameObject> GameObject::create(const std::shared_ptr<Component> & component) {
    return std::make_shared<GameObject>(component);
}