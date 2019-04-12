#include "EngineObject.h"

EngineObject::EngineObject(const std::shared_ptr<GameObject> & gameObject) {
    this->gameObject = gameObject;
}

MeshType EngineObject::getMeshType() {
    return gameObject->getMeshType();
}

std::shared_ptr<Mesh> EngineObject::getMesh() {
    return gameObject->getComponent<Mesh>();
}

std::shared_ptr<MeshPrototype> EngineObject::getMeshPrototype() {
    return gameObject->getComponent<MeshPrototype>();
}

Transform EngineObject::getTransform() {
    return gameObject->transform;
}
