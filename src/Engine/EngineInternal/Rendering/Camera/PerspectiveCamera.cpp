#include "PerspectiveCamera.h"

glm::vec3 PerspectiveCamera::getPosition() {
    return position;
}

glm::mat4x4 PerspectiveCamera::getViewMatrix() {
    return glm::lookAt(position, position + lookDirectionVector, upVector);
}

glm::mat4x4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fovy), aspectRatio, 0.1f, 1000.0f);
}

void PerspectiveCamera::onMouseMove(const glm::vec2 & delta) {
    if (disableMovement) {
        return;
    }

    if (!rightMousePressed) {
        return;
    }

    float sensitivity = 0.05;

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
        } else if (rightMousePressed) {

            rightMousePressed = false;
        }
    }
}

void PerspectiveCamera::onKeyInfoReceived(const KeyInfo & keyInfo) {

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