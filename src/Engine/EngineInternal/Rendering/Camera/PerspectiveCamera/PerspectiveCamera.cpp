#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const glm::vec3 position) : BaseCamera() {
    positionProperty = std::make_shared<Vec3Property>(position);
    lookDirectionVector = normalize(lookAt - position);
    projection = PERSPECTIVE;
    calculateFrustumPlanes();
}

void PerspectiveCamera::onMouseMove(const glm::vec2 & delta) {
    if (disableMovement) return;
    if (!rightMousePressed) return;

    float sensitivity = 0.1;

    yaw += (delta.x * sensitivity);
    pitch += (delta.y * sensitivity);

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 f;

    f.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = -sin(glm::radians(pitch));
    f.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));

    glm::vec3 df = glm::normalize(f) - frontVector;
    frontVector = glm::normalize(f);

    lookDirectionVector += df;
}

void PerspectiveCamera::onMouseButtonPressed(const MouseButtonInfo & info) {
    if (info.button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (info.action == GLFW_PRESS && !rightMousePressed) {
            rightMousePressed = true;
        }
        else if (rightMousePressed) {
            rightMousePressed = false;
        }
    }
}

void PerspectiveCamera::onKeyInfoReceived(const KeyInfo & keyInfo) {
    if (disableMovement) return;

    float speed = 0.5f;

    if (keyInfo.pressedKeys[GLFW_KEY_LEFT_CONTROL]) {
        speed *= 0.1f;
    }

    if (keyInfo.pressedKeys[GLFW_KEY_LEFT_SHIFT]) {
        speed *= 20.0f;
    }

    auto velocitySum = glm::vec3(0.0);

    velocitySum += float(keyInfo.pressedKeys[GLFW_KEY_W]) * lookDirectionVector * speed;
    velocitySum -= float(keyInfo.pressedKeys[GLFW_KEY_S]) * lookDirectionVector * speed;
    velocitySum +=
            float(keyInfo.pressedKeys[GLFW_KEY_A]) * glm::normalize(glm::cross(upVector, lookDirectionVector)) * speed;
    velocitySum -=
            float(keyInfo.pressedKeys[GLFW_KEY_D]) * glm::normalize(glm::cross(upVector, lookDirectionVector)) * speed;

    velocity = velocitySum;
}

void PerspectiveCamera::Update() {

    calculateFrustumPlanes();
    currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    positionProperty->setValue(getPosition() + velocity * deltaTime);
}

void PerspectiveCamera::updateAspectRatio(const glm::vec2 & size) {
    aspectRatio = size.x / size.y;
    calculateFrustumPlanes();
}

void PerspectiveCamera::setPosition(const glm::vec3 & pos) {
    positionProperty->setValue(pos);
    lookDirectionVector = normalize(lookAt - getPosition());
}

glm::vec3 PerspectiveCamera::getPosition() {
    return positionProperty->getValue();
}

glm::mat4x4 PerspectiveCamera::getViewMatrix() {
    return glm::lookAt(getPosition(), getPosition() + lookDirectionVector, upVector);
}

glm::mat4x4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fovy), aspectRatio, 0.1f, 10000.0f);
}

bool PerspectiveCamera::testFrustum(const std::shared_ptr<GameObject> & child) {

    glm::vec3 center = child->transform.position;

    auto bBox = child->boundingBox;

    if (!bBox.get()) {
        return false;
    }

    float radius = std::max(std::max(bBox->transform.scale.x, bBox->transform.scale.y), bBox->transform.scale.z);

    for (int i = 0; i < 6; i++) {
        float dist = planes[i].x * center.x + planes[i].y * center.y + planes[i].z * center.z + planes[i].w - radius;

        if (dist < - radius * 2.0f) {
            return false;
        }
    }
    return true;
}

void PerspectiveCamera::calculateFrustumPlanes() {
    glm::mat matrix = glm::perspective(glm::radians(fovy), aspectRatio, 0.1f, 50.0f) * getViewMatrix();

    planes[Right] = glm::vec4(matrix[0][3] - matrix[0][0],
                              matrix[1][3] - matrix[1][0],
                              matrix[2][3] - matrix[2][0],
                              matrix[3][3] - matrix[3][0]);

    planes[Left] = glm::vec4(matrix[0][3] + matrix[0][0],
                             matrix[1][3] + matrix[1][0],
                             matrix[2][3] + matrix[2][0],
                             matrix[3][3] + matrix[3][0]);

    planes[Bottom] = glm::vec4(matrix[0][3] + matrix[0][1],
                               matrix[1][3] + matrix[1][1],
                               matrix[2][3] + matrix[2][1],
                               matrix[3][3] + matrix[3][1]);

    planes[Top] = glm::vec4(matrix[0][3] - matrix[0][1],
                            matrix[1][3] - matrix[1][1],
                            matrix[2][3] - matrix[2][1],
                            matrix[3][3] - matrix[3][1]);

    planes[Far] = glm::vec4(matrix[0][3] - matrix[0][2],
                            matrix[1][3] - matrix[1][2],
                            matrix[2][3] - matrix[2][2],
                            matrix[3][3] - matrix[3][2]);

    planes[Near] = glm::vec4(matrix[0][3] + matrix[0][2],
                             matrix[1][3] + matrix[1][2],
                             matrix[2][3] + matrix[2][2],
                             matrix[3][3] + matrix[3][2]);
    // Normalize them
    for (int i = 0; i < 6; i++) {
        float invl = sqrt(planes[i].x * planes[i].x +
                          planes[i].y * planes[i].y +
                          planes[i].z * planes[i].z);
        planes[i] /= invl;
    }
}