#include "BaseCamera.h"

BaseCamera::BaseCamera() {
    mousePositionDeltaObserver = createObserver<glm::vec2>([&](glm::vec2 v) { onMouseMove(v); });
    mouseButtonObserver = createObserver<MouseButtonInfo>([&](MouseButtonInfo info) { onMouseButtonPressed(info); });
    keyInfoObserver = createObserver<KeyInfo>([&](KeyInfo info) { onKeyInfoReceived(info); });

    SC.add(InputSystem::Instance().mousePositionDeltaProperty->Subscribe(mousePositionDeltaObserver));
    SC.add(InputSystem::Instance().mouseButtonProperty->Subscribe(mouseButtonObserver));
    SC.add(InputSystem::Instance().keyInfoProperty->Subscribe(keyInfoObserver));
}

void BaseCamera::onMouseMove(const glm::vec2 & delta) {}

void BaseCamera::onMouseButtonPressed(const MouseButtonInfo & info) {}

void BaseCamera::onKeyInfoReceived(const KeyInfo & info) {}

glm::vec3 BaseCamera::getPosition() { return glm::vec3(0.0f); }

BaseCamera::~BaseCamera() {
    SC.unsubscribeAll();
}


