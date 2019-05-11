#include "Rotator.h"

void Rotator::Start() {
    timer.reset();
}

void Rotator::Update() {
    auto t = gameObject->transform;
    auto oldRotation = t.rotation;
    auto oldPos = t.position;

    gameObject->transform.dirty = false;

    if (timer.elapsed() >= 17) {
        timer.reset();
        gameObject->transform.rotation = glm::vec3(oldRotation.x + 0.01f , timer.elapsed(), oldRotation.z + 0.01f);
        gameObject->transform.dirty = true;
    }
}