#include "EngineObject.h"

EngineObject::EngineObject(const std::shared_ptr<GameObject> & gameObject) {
    this->gameObject = gameObject;
}

MeshType EngineObject::getMeshType() {
    return gameObject->getMeshType();
}

std::shared_ptr<MeshPrototype> EngineObject::getMeshPrototype() {
    return gameObject->getMeshPrototype();
}

Transform EngineObject::getTransform() {
    return gameObject->transform;
}
