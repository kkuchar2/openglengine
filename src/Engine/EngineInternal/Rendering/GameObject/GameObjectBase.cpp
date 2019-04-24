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

    auto meshProto = castComponent<MeshPrototype>(component);

    if (meshProto) {
        this->meshProto = meshProto;
    }

    components.push_back(component);
}
