#include "GameObject.h"
#include "../../Behaviour/BehaviourComponent.h"

GameObject::GameObject(const std::shared_ptr<Component> & component) {
    addComponent(component);
}

void GameObject::addComponent(const std::shared_ptr<Component> & component) {
    std::shared_ptr<BehaviourComponent> behaviour = std::dynamic_pointer_cast<BehaviourComponent>(component);

    if (behaviour) {
       behaviour->SetObject(this);
    }

    components.push_back(component);
}

std::shared_ptr<MeshPrototype> GameObject::getMeshPrototype() {
    for (auto & componentPtr : components) {

       auto meshProto = std::dynamic_pointer_cast<MeshPrototype>(componentPtr);

        if (meshProto) {
            return meshProto;
        }
    }

    return nullptr;
}

MeshType GameObject::getMeshType() {
    auto meshProto = getMeshPrototype();

    if (meshProto) {
        return meshProto->meshType;
    }
    return NONE;
}


std::shared_ptr<GameObject> GameObject::create() {
    return std::make_shared<GameObject>();
}

std::shared_ptr<GameObject> GameObject::create(const std::shared_ptr<Component> & component) {
    return std::make_shared<GameObject>(component);
}