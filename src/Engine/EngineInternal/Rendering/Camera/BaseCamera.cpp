#include "BaseCamera.h"

BaseCamera::BaseCamera() {
    mousePositionDeltaObserver = createObserver<glm::vec2>([&](glm::vec2 v) { onMouseMove(v); });
    mousePositionDeltaSubscription = InputSystem::Instance().mousePositionDeltaProperty->Subscribe(mousePositionDeltaObserver);

    mouseButtonObserver = createObserver<MouseButtonInfo>([&](MouseButtonInfo info) { onMouseButtonPressed(info); });
    mouseButtonSubscription = InputSystem::Instance().mouseButtonProperty->Subscribe(mouseButtonObserver);

    keyInfoObserver = createObserver<KeyInfo>([&](KeyInfo info) { onKeyInfoReceived(info); });
    keyInfoSubscription = InputSystem::Instance().keyInfoProperty->Subscribe(keyInfoObserver);
}

void BaseCamera::renderInstanced(const std::shared_ptr<InstancedMeshInfo> & info) {
    std::shared_ptr<Shader> shader = info->mesh->shader;
    shader->use();
    initShaderCommon(shader);
    info->mesh->shaderInit(shader);
    info->mesh->UpdateModelMatrices();
    info->mesh->renderInstanced(info->instanceCount);
}

void BaseCamera::render(const std::shared_ptr<Mesh> & mesh, const Transform & transform) {
    std::shared_ptr<Shader> shader = mesh->shader;
    shader->use();
    initShaderCommon(shader);
    mesh->UpdateModelMatrices();
    mesh->shaderInit(shader);
    mesh->render();
}

void BaseCamera::initShaderCommon(const std::shared_ptr<Shader> & shader) {
    shader->setVec3("cameraPosition", getPosition());
    shader->setMat4("vp", getProjectionMatrix() * getViewMatrix());
}

void BaseCamera::onMouseMove(const glm::vec2 & delta) {}

void BaseCamera::onMouseButtonPressed(const MouseButtonInfo & info) {}

void BaseCamera::onKeyInfoReceived(const KeyInfo & info) {}

glm::vec3 BaseCamera::getPosition() { return glm::vec3(0.0f); }

BaseCamera::~BaseCamera() {
    mousePositionDeltaSubscription->Unsubscribe();
    mouseButtonSubscription->Unsubscribe();
    keyInfoSubscription->Unsubscribe();
}


