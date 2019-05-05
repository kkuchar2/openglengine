#include "Rotator.h"

void Rotator::Start() {
    Component::Start();
}

void Rotator::Update() {
    Component::Update();

    auto t = gameObject->transform;
    auto oldRotation = t.rotation;
    auto oldPos = t.position;

    gameObject->transform.rotation = glm::vec3(oldRotation.x + 0.01f , oldRotation.y + 0.01f, oldRotation.z + 0.01f);
    gameObject->transform.rotationMatrix = MatrixUtils::rotationMatrix(gameObject->transform.rotation);
}