#include "BaseCamera.h"

BaseCamera::BaseCamera() {
    mousePositionDeltaObserver = createObserver<glm::vec2>([&](glm::vec2 v) { onMouseMove(v); });
    mousePositionDeltaSubscription = InputSystem::Instance().mousePositionDeltaProperty->Subscribe(mousePositionDeltaObserver);
}

void BaseCamera::render(const std::shared_ptr<Mesh> & mesh, int instancesCount) {
    std::shared_ptr<Shader> shader = mesh->shader;

    shader->use();

    mesh->shaderInit(shader);

    if (mesh->textureId != 0) {
        glBindTexture(GL_TEXTURE_2D, mesh->textureId);
    }

    mesh->Render(instancesCount);
}

glm::mat4 BaseCamera::createMVP(const std::shared_ptr<EngineObject> & object) {
    glm::mat4 modelMatrix = getModelMatrix();

    glm::mat4 m = glm::translate(getModelMatrix(), object->getTransform().position);
    m *= MatrixUtils::rotationMatrix(object->getTransform().rotation);
    m *= MatrixUtils::scaleMatrix(object->getTransform().scale);

    glm::mat4 mvp = getProjectionMatrix() * getViewMatrix() * m;

    return mvp;
}

void BaseCamera::onMouseMove(const glm::vec2 & delta) { }

void BaseCamera::onMouseButtonPressed(int button, int action) {
    // TODO: Create subscription to InputSystem
}

void BaseCamera::onKeysPressedStateReceived(std::vector<bool> & pressed_keys) {
    // TODO: Create subscription to InputSystem
}

glm::vec3 BaseCamera::getScaleCorrection() {
    return glm::vec3(1.0f);
}

glm::vec3 BaseCamera::getPosition() {
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

BaseCamera::~BaseCamera() {
    mousePositionDeltaSubscription->Unsubscribe();
}
