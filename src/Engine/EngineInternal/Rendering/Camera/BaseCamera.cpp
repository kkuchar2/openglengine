#include "BaseCamera.h"

BaseCamera::BaseCamera() {
    mousePositionDeltaObserver = createObserver<glm::vec2>([&](glm::vec2 v) { onMouseMove(v); });
    mousePositionDeltaSubscription = InputSystem::Instance().mousePositionDeltaProperty->Subscribe(mousePositionDeltaObserver);

    mouseButtonObserver = createObserver<MouseButtonInfo>([&](MouseButtonInfo info) { onMouseButtonPressed(info); });
    mouseButtonSubscription = InputSystem::Instance().mouseButtonProperty->Subscribe(mouseButtonObserver);

    keyInfoObserver = createObserver<KeyInfo>([&](KeyInfo info) { onKeyInfoReceived(info); });
    keyInfoSubscription = InputSystem::Instance().keyInfoProperty->Subscribe(keyInfoObserver);
}

void BaseCamera::render(const std::shared_ptr<Mesh> & mesh, const int & instancesCount) {
    std::shared_ptr<Shader> shader = mesh->shader;

    shader->use();

    shader->setVec3("viewPos", getPosition());
    shader->setMat4("projectionMatrix", getProjectionMatrix());
    shader->setMat4("viewMatrix", getViewMatrix());

    mesh->shaderInit(shader);

    if (mesh->textureId != 0) {
        glBindTexture(GL_TEXTURE_2D, mesh->textureId);
    }

    mesh->Render(instancesCount);
}

glm::mat4 BaseCamera::createModelMatrix(const std::shared_ptr<EngineObject> & object) {
    glm::mat4 modelMatrix = getModelMatrix();
    glm::mat4 m = glm::translate(getModelMatrix(), object->getTransform().position);
    m *= MatrixUtils::rotationMatrix(object->getTransform().rotation);
    m *= MatrixUtils::scaleMatrix(object->getTransform().scale);
    return m;
}

void BaseCamera::onMouseMove(const glm::vec2 & delta) { }

void BaseCamera::onMouseButtonPressed(const MouseButtonInfo & info) {

}

void BaseCamera::onKeyInfoReceived(const KeyInfo & info) {
}

glm::vec3 BaseCamera::getScaleCorrection() {
    return glm::vec3(1.0f);
}

glm::vec3 BaseCamera::getPosition() {
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

BaseCamera::~BaseCamera() {
    mousePositionDeltaSubscription->Unsubscribe();
    mouseButtonSubscription->Unsubscribe();
    keyInfoSubscription->Unsubscribe();
}
