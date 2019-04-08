#include "EngineObject.h"

EngineObject::EngineObject(const std::shared_ptr<GameObject> & gameObject) {
    this->gameObject = gameObject;
}

void EngineObject::prepare() {
    gameObject->prepare();
}

MeshType EngineObject::getMeshType() {
    return gameObject->getMeshType();
}

std::shared_ptr<Mesh> EngineObject::getMesh() {
    return gameObject->getMesh();
}

Transform EngineObject::getTransform() {
    return gameObject->transform;
}
