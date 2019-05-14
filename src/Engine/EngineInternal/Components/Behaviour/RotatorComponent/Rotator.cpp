#include "Rotator.h"

void Rotator::Start() {
    timer.reset();
}

void Rotator::Update() {
    if (timer.elapsed() >= 17) {
        timer.reset();
        auto t = gameObject->transform;
        auto oldRotation = t.rotation;
        auto oldPos = t.position;

        gameObject->transform.dirty = false;
        gameObject->transform.rotation = glm::vec3(oldRotation.x + 0.05, oldRotation.y + 0.05, oldRotation.z + 0.05);
        gameObject->transform.dirty = true;
    }
}