#include "EngineObject.h"

EngineObject::EngineObject(const std::shared_ptr<GameObject> & gameObject) {
    this->gameObject = gameObject;
}

std::shared_ptr<MeshPrototype> EngineObject::getMeshPrototype() {
    return gameObject->getComponent<MeshPrototype>();
}

Transform EngineObject::getTransform() {
    return gameObject->transform;
}

void EngineObject::OnUpdate() {
    gameObject->OnUpdate();
}
