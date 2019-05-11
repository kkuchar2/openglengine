#include "BaseCamera.h"

BaseCamera::BaseCamera() {
    mousePositionDeltaObserver = createObserver<glm::vec2>([&](glm::vec2 v) { onMouseMove(v); });
    mouseButtonObserver = createObserver<MouseButtonInfo>([&](MouseButtonInfo info) { onMouseButtonPressed(info); });
    keyInfoObserver = createObserver<KeyInfo>([&](KeyInfo info) { onKeyInfoReceived(info); });

    SC.add(InputSystem::Instance().mousePositionDeltaProperty->Subscribe(mousePositionDeltaObserver));
    SC.add(InputSystem::Instance().mouseButtonProperty->Subscribe(mouseButtonObserver));
    SC.add(InputSystem::Instance().keyInfoProperty->Subscribe(keyInfoObserver));
}

void BaseCamera::renderInstanced(const std::shared_ptr<MeshInfo> & info) {
    std::shared_ptr<Shader> shader = info->renderer->shader;
    shader->use();
    initShaderCommon(shader);
    info->renderer->shaderInit(shader);
    info->renderer->UpdateModelMatrices();
    info->renderer->UpdateColorVectors();
    info->renderer->renderInstanced(info->renderer->not_culled_indexes.size());
}

void BaseCamera::render(const std::shared_ptr<MeshInfo> & info) {
    std::shared_ptr<Shader> shader = info->renderer->shader;
    shader->use();
    initShaderCommon(shader);
    info->renderer->shaderInit(shader);
    info->renderer->UpdateModelMatrices();
    info->renderer->UpdateColorVectors();
    info->renderer->render();
}

void BaseCamera::initShaderCommon(const std::shared_ptr<Shader> & shader) {
    shader->setBool("showNormals", showNormals);
    shader->setVec3("cameraPosition", getPosition());
    shader->setMat4("vp", getProjectionMatrix() * getViewMatrix());
}

void BaseCamera::onMouseMove(const glm::vec2 & delta) {}

void BaseCamera::onMouseButtonPressed(const MouseButtonInfo & info) {}

void BaseCamera::onKeyInfoReceived(const KeyInfo & info) {}

glm::vec3 BaseCamera::getPosition() { return glm::vec3(0.0f); }

BaseCamera::~BaseCamera() {
    SC.unsubscribeAll();
}


