#include "GameObjectBase.h"
#include <Behaviour/BehaviourComponent.h>

GameObjectBase::GameObjectBase() = default;

GameObjectBase::GameObjectBase(const std::shared_ptr<Component> & component) {
    addComponent(component);
}

void GameObjectBase::addComponent(const std::shared_ptr<Component> & component) {
    auto behaviour = castComponent<BehaviourComponent>(component);

    if (behaviour) {
        behaviour->SetObject(static_cast<GameObject *>(this));
    }

    auto proto = castComponent<MeshPrototype>(component);

    if (proto) {
        meshProto = proto;
    }

    components.push_back(component);
}
